import os
print('Input the test case you want to run!')
x = int(input())

os.system('./clean.sh')

if x == 7:
    com = 'rm BasicDataSet/testcase7/my.out'
    os.system(com)
    for i in range(1, 4):
        print('Running test data', i)
        com = 'time ./code < BasicDataSet/testcase7/' + str(i) + '.txt >> BasicDataSet/testcase7/my.out'
        os.system(com)
    com = 'diff BasicDataSet/testcase7/ans.txt BasicDataSet/testcase7/my.out'
    os.system(com)

if x == 8:
    com = 'rm BasicDataSet/testcase8/my.out'
    os.system(com)
    for i in range(1, 101):
        print('Running test data', i)
        com = 'time ./code < BasicDataSet/testcase8/' + str(i) + '.txt >> BasicDataSet/testcase8/my.out'
        os.system(com)
    com = 'diff BasicDataSet/testcase8/ans.txt BasicDataSet/testcase8/my.out'
    os.system(com)