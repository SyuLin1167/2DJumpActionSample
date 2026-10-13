import fs from 'node:fs'
import path from 'node:path'
import crypto from 'node:crypto'
import { fileURLToPath } from 'node:url'

const docs = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..')
const root = path.resolve(docs, '..')
const walk = dir => fs.readdirSync(dir, { withFileTypes: true }).flatMap(e =>
  ['node_modules', '.npm-cache', '.vitepress', '.git'].includes(e.name) ? [] :
  e.isDirectory() ? walk(path.join(dir, e.name)) : [path.join(dir, e.name)])
const errors = []
const files = [...walk(docs).filter(f => f.endsWith('.md')), path.join(root, 'README.md')]
for (const file of files) {
  const text = fs.readFileSync(file, 'utf8')
  const prose = text.replace(/```[\s\S]*?```/g, '')
  if (/2DJumpActionSample/.test(prose)) errors.push(`${file}: old repository name`)
  if (/[A-Za-z]:[\\/]Users[\\/]/i.test(text)) errors.push(`${file}: user-specific local path`)
  for (const match of prose.matchAll(/\]\(([^)]+)\)/g)) {
    const target = match[1].split('#')[0]
    if (!target || /^(https?:|mailto:)/.test(target)) continue
    const absolute = target.startsWith('/') ? path.join(docs, target) : path.resolve(path.dirname(file), target)
    if (![absolute, `${absolute}.md`, path.join(absolute, 'index.md')].some(p => fs.existsSync(p)))
      errors.push(`${path.relative(root, file)}: missing link ${target}`)
  }
}
const manifest = JSON.parse(fs.readFileSync(path.join(docs, 'api/source-manifest.json'), 'utf8'))
const actual = [...walk(path.join(root, 'ProjectName/code')), ...walk(path.join(root, 'ProjectName/include/MyLib'))]
  .filter(f => f.endsWith('.ixx')).map(f => path.relative(root, f).replaceAll('\\', '/'))
for (const file of actual) if (!manifest.modules.some(r => r.source === file)) errors.push(`New undocumented module: ${file}`)
for (const record of manifest.modules) {
  const file = path.join(root, record.source)
  if (!fs.existsSync(file)) { errors.push(`Removed module: ${record.source}`); continue }
  const source = fs.readFileSync(file, 'utf8').replace(/^\uFEFF/, '').replace(/\r\n/g, '\n')
  const hash = crypto.createHash('sha256').update(source).digest('hex')
  if (hash !== record.sha256) errors.push(`API review required: ${record.source}`)
  const page = fs.readFileSync(path.join(docs, 'api/source', `${record.slug}.md`), 'utf8')
  if (!page.includes('```cpp\n' + source.trim() + '\n```')) errors.push(`Source excerpt drift: ${record.module}`)
}
for (const record of manifest.reviewedFiles) {
  const file = path.join(root, record.source)
  if (!fs.existsSync(file)) { errors.push(`Reviewed source removed: ${record.source}`); continue }
  const content = fs.readFileSync(file, 'utf8').replace(/^\uFEFF/, '').replace(/\r\n/g, '\n')
  if (crypto.createHash('sha256').update(content).digest('hex') !== record.sha256)
    errors.push(`Documentation review required: ${record.source}`)
}
if (errors.length) { console.error(errors.join('\n')); process.exitCode = 1 }
else console.log(`Checked ${files.length} Markdown files and ${manifest.modules.length} module snapshots.`)
