const ghpages = require('gh-pages')
const BRANCH = 'gh-pages'
const TODAY = new Date().toLocaleString()
const FOLDER_DIST = 'dist'

console.log(`start publishing folder ${FOLDER_DIST} to ${BRANCH}`)

ghpages.publish(FOLDER_DIST, {
  branch: BRANCH,
  message: `Publishing folder ${FOLDER_DIST} to ${BRANCH} in ${TODAY}`
}, () => {
  console.log(`done publishing folder ${FOLDER_DIST} to ${BRANCH}`)
})