import fs from 'node:fs'
import path from 'node:path'
import crypto from 'node:crypto'
import { fileURLToPath } from 'node:url'

const docs = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..')
const root = path.resolve(docs, '..')
const revision = '08f9fa53fa5e9043d46aeede8e7aab7bab519892'
const walk = dir => fs.readdirSync(dir, { withFileTypes: true }).flatMap(e =>
  e.isDirectory() ? walk(path.join(dir, e.name)) : [path.join(dir, e.name)])
const files = [...walk(path.join(root, 'ProjectName/code')), ...walk(path.join(root, 'ProjectName/include/MyLib'))]
  .filter(f => f.endsWith('.ixx')).sort()
const groupFor = p => p.includes('/include/MyLib/') ? 'mylib' : ({
  GameSystem: 'game-system', Object: 'object', Component: 'component', Collision: 'collision',
  Asset: 'asset', Scene: 'scene', UI: 'ui'
})[p.split('/')[2]]
const records = []
fs.mkdirSync(path.join(docs, 'api/source'), { recursive: true })
for (const file of files) {
  const content = fs.readFileSync(file, 'utf8').replace(/^\uFEFF/, '').replace(/\r\n/g, '\n')
  const module = content.match(/export\s+module\s+([\w.]+)\s*;/)?.[1]
  if (!module) throw new Error(`Module name missing: ${file}`)
  const source = path.relative(root, file).replaceAll('\\', '/')
  const slug = module.toLowerCase().replaceAll('.', '-')
  if (records.some(r => r.slug === slug)) throw new Error(`Duplicate slug: ${slug}`)
  const group = groupFor(source)
  const summary = [...content.matchAll(/<summary>([\s\S]*?)<\/summary>/g)]
    .slice(0, 2).map(m => m[1].replace(/\/\/\//g, '').trim()).join(' / ')
  const sourceUrl = `https://github.com/SyuLin1167/2DGameSample/blob/${revision}/${source}`
  const body = `# ${module}\n\n${summary || '公開モジュールのソース参照。'}\n\n` +
    `所属：[${group}のAPI解説](../${group}.md) · [全モジュール索引](../modules.md)\n\n` +
    `## 読み方\n\nこのページは実ファイルから生成したソース照合用資料です。公開関数の引数・戻り値の型、オーバーロード、列挙値を確認できます。public／protected／privateを区別し、privateメンバーを呼び出し例に使わないでください。コメントは原文であり、古い説明や誤記を含む場合があります。利用条件・訂正は上記のAPI解説と[既知の制約](../../project/status.md)を優先してください。\n\n` +
    `元ファイル：[${source}](${sourceUrl})。確認基準：\`${revision.slice(0, 8)}\`。\n\n` +
    `## インターフェースとインライン実装\n\n\`\`\`cpp\n${content.trim()}\n\`\`\`\n`
  fs.writeFileSync(path.join(docs, 'api/source', `${slug}.md`), body)
  records.push({ module, source, slug, group, sha256: crypto.createHash('sha256').update(content).digest('hex') })
}
fs.writeFileSync(path.join(docs, 'api/modules.md'), '# 全モジュール索引\n\nすべての自作モジュールインターフェース（.ixx）とソースへの入口です。生成資料は正確な宣言を確認する補助資料で、利用条件は[API解説](./index.md)を参照します。ゲームの実装ファイルは変更していません。\n\n' +
  '| モジュール | API分類 |\n| --- | --- |\n' + records.map(r => `| [${r.module}](./source/${r.slug}.md) | [${r.group}](./${r.group}.md) |`).join('\n') + '\n')
const reviewedFiles = [
  ...walk(path.join(root, 'ProjectName/code')), ...walk(path.join(root, 'ProjectName/include/MyLib')),
  path.join(root, 'setup.bat'), path.join(root, 'ProjectName/project/project.vcxproj')
].filter(f => /\.(ixx|cpp|bat|vcxproj)$/.test(f)).sort().map(file => ({
  source: path.relative(root, file).replaceAll('\\', '/'),
  sha256: crypto.createHash('sha256').update(fs.readFileSync(file, 'utf8').replace(/^\uFEFF/, '').replace(/\r\n/g, '\n')).digest('hex')
}))
fs.writeFileSync(path.join(docs, 'api/source-manifest.json'), JSON.stringify({ revision, modules: records, reviewedFiles }, null, 2) + '\n')
console.log(`Generated ${records.length} module reference pages.`)
