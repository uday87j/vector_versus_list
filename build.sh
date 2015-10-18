g++ \
--std=c++11 \
-O3 \
-Wall \
test.cpp
#-DBOOST_SYSTEM_NO_DEPRECATED \
#-L /mnt/hgfs/share_host_vm/code/boost_1_59_0/libs/ \
#-lboost_system \
#-lboost_thread \
