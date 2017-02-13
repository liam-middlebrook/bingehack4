node {
 stage 'checkout' {
    checkout poll: true, scm: scm
 }

 stage 'build' {
    sh './travis-build'
 }
}
