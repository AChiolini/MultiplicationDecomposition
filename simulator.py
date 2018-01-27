import random as rand
import subprocess
import os

BASE_COMMAND = './main %d %d %d %d'

f = open('error.log', 'w')
f.write('')
f.close()

def func():
    for i in range(3, 63):
        commands = []
        for j in range(3, 63-i):
            rand1 = rand.randint(0, 2^(i-1)-1)
            rand2 = rand.randint(0, 2^(j-1)-1)
            commands.append('./main %d %d %d %d' % (i, j, rand1, rand2))
            commands.append('./main %d %d -%d %d' % (i, j, rand1, rand2))
            commands.append('./main %d %d %d -%d' % (i, j, rand1, rand2))
            commands.append('./main %d %d -%d -%d' % (i, j, rand1, rand2))
            commands.append('./main %d %d %d %d' % (i, j, -2^(i-1), rand2))
            commands.append('./main %d %d %d %d' % (i, j, rand1, -2^(j-1)))
        for c in commands:
            output = str(subprocess.Popen(c, shell = True, stdout=subprocess.PIPE).communicate()[0])
            #os.system(c)
            print((output))
            #print(output.split('Obtained value: ')[1])
            parts = output.split('Output Length:')
            for part in parts:
                if part.find('Expected value: ')!= -1:
                    a1 = part.split('Expected value: ')[1]
                    a = a1.split('Obtained')[0]
                    pt2 = part.split('Expected value: ')[1]
                    if pt2.find('Obtained value: ') != -1:
                        b = pt2.split('Obtained value: ')[1].split('Output')[0]
                    else:
                        print('No obtained value found')
                    if a != b:
                        f = open('error.log', 'a')
                        f.write(part.split('Expression')[0] + '\n' + c + '\n\n\n\n\n')
                        f.close()
                else:
                    continue

if __name__ == '__main__':
    func()