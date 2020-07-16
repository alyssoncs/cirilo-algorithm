pipeline {
	agent any
	stages {
		stage('build') {
			steps {
				sh 'mkdir obj'
				sh 'mkdir bin'
				sh 'make'
			}
		}

		stage('test') {
			steps {
				sh 'bin/test 2 10000 1'
			}
		}

		stage('clean') {
			steps {
				sh 'rm -R obj'
				sh 'rm -R bin'
			}
		}
	}

}
				
