import random as rand
import subprocess
import os

BASE_COMMAND = './main %d %d %d %d'

f = open('error.log', 'w')
f.write('')
f.close()

def test_function():
    # Range for x goes from 2 (because the minimum length of an operand is 2) to 58,
    # so we will have at most a multiplication 2 x 58
    for i in range(2, 59):
        commands = []
        # Same here but when i will be 58 j must be at most 2, so 61 - 58
        for j in range(2, 61 - i):
            rand1 = (int(round(rand.random() * ((2**(i-1))-1))))
            rand2 = (int(round(rand.random() * ((2**(j-1))-1))))
            commands.append('./main %d %d %d %d' % (i, j, rand1, rand2))
            rand1 = (int(round(rand.random() * ((2**(i-1))-1))))
            rand2 = (int(round(rand.random() * ((2**(j-1))-1))))
            commands.append('./main %d %d -%d %d' % (i, j, rand1, rand2))
            rand1 = (int(round(rand.random() * ((2**(i-1))-1))))
            rand2 = (int(round(rand.random() * ((2**(j-1))-1))))
            commands.append('./main %d %d %d -%d' % (i, j, rand1, rand2))
            rand1 = (int(round(rand.random() * ((2**(i-1))-1))))
            rand2 = (int(round(rand.random() * ((2**(j-1))-1))))
            commands.append('./main %d %d -%d -%d' % (i, j, rand1, rand2))
            rand2 = (int(round(rand.random() * ((2**(j-1))-1))))
            commands.append('./main %d %d %d %d' % (i, j, -2**(i-1), rand2))
            rand1 = (int(round(rand.random() * ((2**(i-1))-1))))
            commands.append('./main %d %d %d %d' % (i, j, rand1, -2**(j-1)))
        print("Executing %d x %d multiplications." % (i, j))
        for c in commands:
            output = str(subprocess.Popen(c, shell = True, stdout=subprocess.PIPE).communicate()[0])
            #os.system(c)
            #print((output))
            #print(output.split('Obtained value: ')[1])
            if (output.find('Execution time') == -1):
                f = open('error.log', 'a')
                f.write("Program doesn't run correctly.\n" + c + '\n\n\n')
                f.close()
            parts = output.split('\n\n\n')
            for part in parts:
                if part.find('Expected value: ')!= -1:
                    part2 = part.split('Expected value: ')[1]
                    a = part2.split('Obtained value: ')[0]
                    a = a.split('\n')[0]
                    b = part2.split('Obtained value: ')[1]
                    b = b.split('\n')[0]
                    if a != b:
                        f = open('error.log', 'a')
                        f.write(part.split('Expression')[0] + '\n' + c + '\n\n\n\n')
                        f.close()

if __name__ == '__main__':
    test_function()