node default{

  include apt
  exec { 'apt-upgrade':
    command   => '/usr/bin/apt-get --quiet --yes --fix-broken upgrade',
    logoutput => 'on_failure',
    path      => '/usr/bin:/usr/sbin:/bin:/usr/local/bin:/usr/local/sbin:/sbin',
  }

  include git
  include gcc
  include cmake

  class { 'python' :
    version    => 'system',
    pip        => 'present',
    dev        => 'present',
    virtualenv => 'present',
  }

  include opencv

}
