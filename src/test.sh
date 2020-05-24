#!/bin/sh


function testfemesh() {
./femesh ../$1.xyc -o ../tmp.mesh
echo -n $1
diff ../tmp.mesh ../$1.mesh > ../tmp.log
if [ -s ../tmp.log ];then
    echo  "  ..... NG"
else
    echo  "  ..... OK"
fi
rm -f ../tmp.mesh ../tmp.log
}


testfemesh  kanto
testfemesh  pt
testfemesh  square
