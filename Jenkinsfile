node {
 stage 'Checkout'
 checkout scm

 stage 'Build'
 sh './travis-build'

 stage 'Run'
 sh './a.out'
}
