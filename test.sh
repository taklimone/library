#!/bin/sh

CXX=${CXX:-g++}
CXXFLAGS=${CXXFLAGS:--std=c++14 -I./include -O2 -Wall}

geturl() {
    file=$1
    cat $file | grep '^#define PROBLEM' | sed 's/^#define PROBLEM //'
}

getid() {
    file=$1
    cat $file | grep '^#define PROBLEM' | sed 's/^#define PROBLEM http:\/\/judge.u-aizu.ac.jp\/onlinejudge\/description.jsp?id=//'
}

download() {
    url=$1
    id=$2
    for num in `seq 1 500`; do
        dir=test/$id/$num
        mkdir -p $dir
        wget -q -O $dir/in "https://judgedat.u-aizu.ac.jp/testcases/$id/$num/in"
        wget -q -O $dir/out "https://judgedat.u-aizu.ac.jp/testcases/$id/$num/out"
        grep -q 'not available' $dir/in
        if [ $? -eq 0 ]; then
            rm -rf $dir
            return $((num-1))
        fi
    done
}

verify() {
    file=$1
    url=$(geturl $file)
    problem=$(getid $file)

    if [ -z $problem ]; then
        echo -e "\e[33;1mWARNING\e[m: $file : PROBLEM not defined"
        return 0
    fi

    dir=test/$problem
    mkdir -p $dir

    # download testcases
    num=$(download $url $problem)

    # compile
    $CXX $CXXFLAGS -o $dir/a.out $file

    # run
    for casenum in `seq 1 $num`; do
        diff <(./$dir/a.out < $dir/$casenum/in) <(cat $dir/$casenum/out) &> /dev/null
        if [ $? -ne 0 ]; then
            rm -rf $dir
            echo -e "\e[31;1mFAILED\e[m: $file"
            return 1
        fi
    done
    
    rm -rf $dir
    echo -e "\e[32;1mPASSED\e[m: $file"
    return 0
}

run() {
    failed=0
    for file in `find ./test -name *.cpp`; do
        verify $file
        if [ $? -ne 0 ]; then
            failed=$((failed+1))
        fi
    done

    if [ $failed -eq 0 ]; then
        return 0
    else
        return 1
    fi
}

run
