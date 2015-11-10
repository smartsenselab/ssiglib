#Install clang
class clang{

  $packages = [
    'clang',
  ]

  package { $packages: ensure => latest }

}
