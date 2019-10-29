#!/bin/sh

CXX=${CXX:-g++}
CXXFLAGS=${CXXFLAGS:--std=c++1z -O2 -Wall}

get-url() {
    file=$1
    cat $file | grep '^#define PROBLEM' | sed 's/^#define PROBLEM //'
}

get-id() {
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
    url=$(get-url $file)
    problem=$(get-id $file)

    if [ -z $problem ]; then
        echo "WARNING: $file : PROBLEM not defined"
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
        diff <(./$dir/a.out < $dir/$casenum/in) <(cat $dir/$casenum/out)
        if [ $? -ne 0 ]; then
            echo "FAILED: $file"
            exit 1
        fi
    done
    
    rm -rf $dir
    echo "PASSED: $file"
}

run() {
    for file in test/*.cpp; do
        verify $file
    done
}

run
