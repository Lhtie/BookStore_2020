import os
print('Input the test case you want to run!')
x = int(input())

os.system('./clean.sh')

if x == 1:
    com = 'rm my.out'
    os.system(com)
    for i in range(1, 11):
        print('Running test data', i)
        com = 'time ./code < AdvancedDataSet/testcase1/' + str(i) + '.in > AdvancedDataSet/testcase1/my' + str(i) + '.out'
        os.system(com)
        com = 'diff AdvancedDataSet/testcase1/' + str(i) + '.out AdvancedDataSet/testcase1/my' + str(i) + '.out'
        os.system(com)

if x == 2:
    com = 'rm my.out'
    os.system(com)
    for i in range(1, 11):
        print('Running test data', i)
        com = 'time ./code < AdvancedDataSet/testcase2/' + str(i) + '.in > AdvancedDataSet/testcase2/my' + str(i) + '.out'
        os.system(com)
        com = 'diff AdvancedDataSet/testcase2/' + str(i) + '.out AdvancedDataSet/testcase2/my' + str(i) + '.out'
        os.system(com)

if x == 3:
    com = 'rm my.out'
    os.system(com)
    for i in range(1, 6):
        print('Running test data', i)
        com = 'time ./code < AdvancedDataSet/testcase3/' + str(i) + '.in > AdvancedDataSet/testcase3/my' + str(i) + '.out'
        os.system(com)
        com = 'diff AdvancedDataSet/testcase3/' + str(i) + '.out AdvancedDataSet/testcase3/my' + str(i) + '.out'
        os.system(com)

if x == 4:
    com = 'rm my.out'
    os.system(com)
    for i in range(1, 11):
        print('Running test data', i)
        com = 'time ./code < AdvancedDataSet/testcase4/' + str(i) + '.in > AdvancedDataSet/testcase4/my' + str(i) + '.out'
        os.system(com)
        com = 'diff AdvancedDataSet/testcase4/' + str(i) + '.out AdvancedDataSet/testcase4/my' + str(i) + '.out'
        os.system(com)

if x == 5:
    com = 'rm my.out'
    os.system(com)
    for i in range(1, 11):
        print('Running test data', i)
        com = 'time ./code < AdvancedDataSet/testcase5/' + str(i) + '.in > AdvancedDataSet/testcase5/my' + str(i) + '.out'
        os.system(com)
        com = 'diff AdvancedDataSet/testcase5/' + str(i) + '.out AdvancedDataSet/testcase5/my' + str(i) + '.out'
        os.system(com)
