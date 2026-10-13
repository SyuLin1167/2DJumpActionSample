import { defineConfig } from 'vitepress'

const section = (text: string, prefix: string, entries: [string, string][]) => ({
  text, collapsed: false, items: entries.map(([name, slug]) => ({ text: name, link: `/${prefix}/${slug}` }))
})
const guide = section('利用ガイド', 'guide', [
  ['はじめに', 'index'], ['環境構築', 'environment'], ['導入・ビルド・実行', 'quickstart'],
  ['操作方法', 'controls'], ['基本構造', 'structure'], ['更新と寿命', 'lifecycle'],
  ['ゲーム制作を始める', 'first-game'], ['困ったときは', 'troubleshooting']
])
const tutorials = section('チュートリアル', 'tutorials', [
  ['実習の進め方', 'index'], ['01 GameObject', 'game-object'], ['02 Component', 'component'],
  ['03 入力と移動', 'input'], ['04 衝突処理', 'collision'], ['05 アニメーション', 'animation'],
  ['06 サウンド', 'sound'], ['07 シーン', 'scene'], ['08 小さなゲーム', 'mini-game']
])
const api = section('APIリファレンス', 'api', [
  ['APIの読み方', 'index'], ['GameSystem', 'game-system'], ['Object', 'object'],
  ['Component', 'component'], ['Collision', 'collision'], ['Asset', 'asset'],
  ['Scene', 'scene'], ['UI', 'ui'], ['MyLib', 'mylib'], ['全モジュール索引', 'modules']
])
const architecture = section('設計解説', 'architecture', [
  ['設計の全体像', 'index'], ['Modulesと依存関係', 'modules'], ['コンポーネント', 'components'],
  ['Visitorと衝突処理', 'collision'], ['非同期読み込み', 'loading'],
  ['所有権と寿命', 'ownership'], ['アニメーションと音声', 'assets']
])
const project = section('プロジェクト情報', 'project', [
  ['実装状況・制約', 'status'], ['ライセンス・素材', 'credits'], ['掲載素材の準備', 'media'],
  ['教材としての利用', 'education'], ['サイトの開発・公開', 'documentation'], ['検証記録', 'verification']
])
export default defineConfig({
  lang: 'ja-JP', title: '2DGameSample', description: 'C++とDxLibで学ぶ、2Dゲーム制作の仕組み。',
  base: '/2DGameSample/', cleanUrls: false, lastUpdated: false,
  markdown: { theme: { light: 'github-light', dark: 'github-dark' } },
  themeConfig: {
    nav: [
      { text: '利用ガイド', link: '/guide/' }, { text: 'チュートリアル', link: '/tutorials/' },
      { text: 'API', link: '/api/' }, { text: '設計解説', link: '/architecture/' }
    ],
    sidebar: {
      '/guide/': [guide, { ...tutorials, collapsed: true }, { ...project, collapsed: true }],
      '/tutorials/': [tutorials, { ...api, collapsed: true }],
      '/api/': [api, { ...architecture, collapsed: true }],
      '/architecture/': [architecture, { ...api, collapsed: true }],
      '/project/': [project, { ...guide, collapsed: true }]
    },
    outline: { label: 'このページの内容', level: [2, 3] },
    docFooter: { prev: '前のページ', next: '次のページ' },
    sidebarMenuLabel: 'メニュー', returnToTopLabel: 'ページ上部へ',
    darkModeSwitchLabel: '表示テーマ', lightModeSwitchTitle: 'ライトモードへ', darkModeSwitchTitle: 'ダークモードへ',
    socialLinks: [{ icon: 'github', link: 'https://github.com/SyuLin1167/2DGameSample' }],
    search: { provider: 'local', options: {
      locales: { root: { translations: {
        button: { buttonText: '検索', buttonAriaLabel: 'ドキュメントを検索' },
        modal: { noResultsText: '見つかりませんでした', resetButtonTitle: '検索をクリア',
          footer: { selectText: '選択', navigateText: '移動', closeText: '閉じる' } }
      } } },
      miniSearch: { options: { tokenize: (text: string) => {
        const segments = [...new Intl.Segmenter('ja', { granularity: 'word' }).segment(text)]
        return segments.filter(s => s.isWordLike).map(s => s.segment)
      } }, searchOptions: { prefix: true, fuzzy: 0.2 } }
    } },
    footer: { message: 'コード確認基準：08f9fa53 · C++実機検証は別途実施', copyright: '2DGameSample · 学びながら組み立てる2Dゲーム開発' }
  }
})
