import os
print('Input the test case you want to run!')
x = int(input())

os.system('./clean.sh')

if x == 1:
    com = 'rm my.out'
    os.system(com)
    for i in range(1, 11):
        print('Running test data', i)
        com = 'time ./code < ComplexDataSet/testcase1/' + str(i) + '.in > ComplexDataSet/testcase1/my' + str(i) + '.out'
        os.system(com)
        com = 'diff ComplexDataSet/testcase1/' + str(i) + '.out ComplexDataSet/testcase1/my' + str(i) + '.out'
        os.system(com)

if x == 2:
    com = 'rm my.out'
    os.system(com)
    for i in range(1, 11):
        print('Running test data', i)
        com = 'time ./code < ComplexDataSet/testcase2/' + str(i) + '.in > ComplexDataSet/testcase2/my' + str(i) + '.out'
        os.system(com)
        com = 'diff ComplexDataSet/testcase2/' + str(i) + '.out ComplexDataSet/testcase2/my' + str(i) + '.out'
        os.system(com)

if x == 3:
    com = 'rm my.out'
    os.system(com)
    for i in range(1, 11):
        print('Running test data', i)
        com = 'time ./code < ComplexDataSet/testcase3/' + str(i) + '.in > ComplexDataSet/testcase3/my' + str(i) + '.out'
        os.system(com)
        com = 'diff ComplexDataSet/testcase3/' + str(i) + '.out ComplexDataSet/testcase3/my' + str(i) + '.out'
        os.system(com)

if x == 4:
    com = 'rm my.out'
    os.system(com)
    for i in range(1, 11):
        print('Running test data', i)
        com = 'time ./code < ComplexDataSet/testcase4/' + str(i) + '.in > ComplexDataSet/testcase4/my' + str(i) + '.out'
        os.system(com)
        com = 'diff ComplexDataSet/testcase4/' + str(i) + '.out ComplexDataSet/testcase4/my' + str(i) + '.out'
        os.system(com)

if x == 5:
    com = 'rm my.out'
    os.system(com)
    for i in range(1, 11):
        print('Running test data', i)
        com = 'time ./code < ComplexDataSet/testcase5/' + str(i) + '.in > ComplexDataSet/testcase5/my' + str(i) + '.out'
        os.system(com)
        com = 'diff ComplexDataSet/testcase5/' + str(i) + '.out ComplexDataSet/testcase5/my' + str(i) + '.out'
        os.system(com)
