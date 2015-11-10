#Install latest opencv
class opencv{

  # sudo apt-get install -qq libboost-filesystem1.54-dev libboost-log1.54-dev
  # libboost-date-time1.54-dev libboost-thread1.54-dev

  $packages = [
    'libgtk2.0-dev',
    'pkg-config',
    'libavcodec-dev',
    'libavformat-dev',
    'libswscale-dev',
    'libtbb2',
    'libtbb-dev',
    'libjpeg-dev',
    'libpng-dev',
    'libtiff-dev',
    'libjasper-dev',
    'libdc1394-22-dev',
    'python-numpy',
  ]

  package { $packages: ensure => latest }

  vcsrepo { '/tmp/opencv-git-clone':
    ensure   => present,
    provider => git,
    source   => 'git://github.com/Itseez/opencv.git',
  }

  file { '/tmp/opencv-git-clone/build':
    ensure  => directory,
    require => Vcsrepo['/tmp/opencv-git-clone'],
  }

  exec {'opencv cmake pre':
    require => File['/tmp/opencv-git-clone/build'],
    command => 'cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=OFF -D WITH_FFMPEG=OFF -D WITH_OPENMP=OFF -D BUILD_opencv_apps=OFF -D BUILD_DOCS=OFF -D BUILD_PERF_TESTS=OFF -D BUILD_TESTS=OFF -D BUILD_WITH_DEBUG_INFO=OFF -D BUILD_ANDROID_SERVICE=OFF ..',
    cwd     => '/tmp/opencv-git-clone/build',
    path    => '/usr/bin:/usr/sbin/:/bin:/sbin'
  }

  exec {'opencv cmake build':
    require => Exec['opencv cmake pre'],
    command => 'cmake --build .',
    cwd     => '/tmp/opencv-git-clone/build',
    path    => '/usr/bin:/usr/sbin/:/bin:/sbin',
    timeout => 1800,
  }

  exec {'opencv cmake install':
    require => Exec['opencv cmake build'],
    command => 'cmake --build . --target install',
    cwd     => '/tmp/opencv-git-clone/build',
    path    => '/usr/bin:/usr/sbin/:/bin:/sbin'
  }

  exec {'opencv ldconfig':
    require => Exec['opencv cmake install'],
    command => 'sh -c \'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf && ldconfig\'',
    path    => '/usr/bin:/usr/sbin/:/bin:/sbin'
  }

}
