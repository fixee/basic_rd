#! /bin/sh

target_dir="/home/xiongfei/.lib"
if [ ! -d $target_dir ]; then
    mkdir $target_dir
    cd $target_dir
fi

tmp_dist="/home/xiongfei/.lib/dist"
cpu_cores=4

# ------ buid libevhtp -----------
lib_dir_name="libevhtp-1.2.10"
lib_download_name="1.2.10.tar.gz"
if [ ! -d $lib_dir_name ]; then
    echo "build libevhtp start"
    wget 'https://github.com/ellzey/libevhtp/archive/1.2.10.tar.gz'
    tar xzvf $lib_download_name
    if [ -d $tmp_dist ]; then 
        rm -rf $tmp_dist/*
    fi
    cd $lib_dir_name
    mkdir build 
    cd build
    cmake .. -DCMAKE_INSTALL_PREFIX=$tmp_dist
    make -j$cpu_cores && make install
    cd ../..
    rm -rf "1.2.10.tar.gz"
    rm -rf "libevhtp-1.2.10"
    mv $tmp_dist $lib_dir_name
    echo "build libevhtp complete"
fi


# -------- build libconfig ----------
lib_download_name="v1.5.tar.gz"
lib_dir_name="libconfig-1.5"
if [ ! -d $lib_dir_name ]; then
    echo "build libconfig start"
    wget 'https://github.com/hyperrealm/libconfig/archive/v1.5.tar.gz'
    tar xzvf $lib_download_name
    cd $lib_dir_name
    aclocal
    autoconf
    automake
    ./configure --prefix=$tmp_dist --enable-shared=false
    make -j$cpu_cores
    make install
    cd ..
    rm -rf $lib_download_name
    rm -rf $lib_dir_name
    mv $tmp_dist $lib_dir_name
    echo "build libconfig end"
fi

# --------- build xxxxxxx------------
