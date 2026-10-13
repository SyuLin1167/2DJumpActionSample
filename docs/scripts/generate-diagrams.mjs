import fs from 'node:fs'
import path from 'node:path'
import { fileURLToPath } from 'node:url'

const dir = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '../public/diagrams')
fs.mkdirSync(dir, { recursive: true })
const esc = s => s.replaceAll('&', '&amp;').replaceAll('<', '&lt;').replaceAll('>', '&gt;')
const diagrams = [
  ['frame', '1フレームの流れ', '上から順に処理し、次のフレームへ進む', [
    ['01 入力と時間', 'SceneManager：キー・マウス・フレーム時間を更新'],
    ['02 オブジェクトの更新', 'Component → GameObject.Update：移動量を決める'],
    ['03 衝突と移動', 'ColliderManager.Step：判定・押し戻し・接触処理'],
    ['04 結果を反映', 'LateUpdate → カメラ更新 → 追加・削除の反映'],
    ['05 描画とシーン切り替え', '描画 → フレーム終端でシーンコマンドを適用'],
  ]],
  ['loading', '読み込みから次のシーンへ', '登録・実行・反映の担当を分ける', [
    ['メイン：タスクを登録', 'LoadingScene → 次シーンの構築 → AddTask'],
    ['メイン：実行開始', '全タスクの登録後に Run'],
    ['ワーカー：段階ごとに実行', 'DATA → INIT → GRAPH → SOUND → FINAL'],
    ['ワーカー：反映を予約', 'PostToMain：共有状態への変更をメインへ渡す'],
    ['メイン：結果を反映', '毎フレーム PumpMain → 完了・失敗を判定'],
    ['成功した場合：次シーンを初期化', '次シーン.Init → プレイ開始'],
  ]],
  ['ownership', 'シーン内の所有関係', '矢印は所有を表す。処理順ではない', [
    ['SceneManager', 'shared_ptr で SceneBase を保持'],
    ['SceneBase', 'unique_ptr で ObjectManager を所有'],
    ['ObjectManager', 'shared_ptr で GameObject を保持'],
    ['GameObject / ComponentManager', 'shared_ptr で各 Component を保持'],
  ]],
  ['visitor', '矩形と円の衝突：呼び出しの流れ', '発行側と相手側、2つの型で処理を選ぶ', [
    ['01 ColliderManager.Step', '矩形を発行側、円を相手として組合せを処理'],
    ['02 RectCollider.CollideWith', '自分が持つ RectColliderVisitor を相手へ渡す'],
    ['03 CircleCollider.Accept', '具体的な円の型で Visitor.Visit を呼ぶ'],
    ['04 RectColliderVisitor.Visit(CircleCollider&)', '矩形 × 円に対応する判定・解決処理へ進む'],
  ]],
]
for (const [name, title, subtitle, rows] of diagrams) {
  const height = 122 + rows.length * 104
  const nodes = rows.map(([head, body], i) => {
    const y = 96 + i * 104
    return `${i ? `<path d="M320 ${y-25}v20" stroke="#337e72" stroke-width="2" marker-end="url(#arrow)"/>` : ''}<rect x="20" y="${y}" width="600" height="78" rx="10" fill="#edf5f2" stroke="#91b7ad"/><text x="40" y="${y+29}" font-size="20" font-weight="700">${esc(head)}</text><text x="40" y="${y+56}" font-size="16">${esc(body)}</text>`
  }).join('\n')
  fs.writeFileSync(path.join(dir, `${name}.svg`), `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 640 ${height}" role="img" aria-labelledby="title desc"><title id="title">${esc(title)}</title><desc id="desc">${esc(subtitle)}。${rows.map(r=>r.map(esc).join('：')).join('。')}</desc><defs><marker id="arrow" markerWidth="8" markerHeight="8" refX="6" refY="3" orient="auto"><path d="M0 0L6 3L0 6" fill="#337e72"/></marker></defs><rect width="640" height="${height}" rx="12" fill="#fff"/><g font-family="'Yu Gothic',sans-serif" fill="#233e38"><text x="24" y="38" font-size="25" font-weight="700">${esc(title)}</text><text x="24" y="68" font-size="16">${esc(subtitle)}</text>${nodes}</g></svg>\n`)
}
console.log(`Generated ${diagrams.length} diagrams.`)
