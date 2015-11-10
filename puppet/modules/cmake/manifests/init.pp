#Install cmake
class cmake{

  $packages = [
    'cmake',
  ]

  package { $packages: ensure => latest }

}
