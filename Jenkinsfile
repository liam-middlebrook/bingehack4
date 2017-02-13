node {
 stage 'Checkout' {
    checkout poll: true, scm: scm
 }

 stage 'Build' {
    sh './travis-build'
 }
}
