# Note by grhkm:
# I cannot figure out how output_validators given in the directory works
# So I modified the testing_tool to work with testing solutions instead

import glob
import argparse
import subprocess
import sys
import traceback

DEBUG = False


def write(p, line):
    assert p.poll() is None, 'Program terminated early'
    if DEBUG:
        print('Write: {}'.format(line), flush=True)
    p.stdin.write('{}\n'.format(line))
    p.stdin.flush()


def read(p):
    assert p.poll() is None, 'Program terminated early'
    line = p.stdout.readline().strip()
    assert line != '', 'Read empty line or closed output pipe. Make sure that your program started successfully.'
    if DEBUG:
        print('Read: %s' % line, flush=True)
    return line


def wrong_answer(p, reason):
    sys.stdout.write('%s\n' % reason)
    p.kill()


parser = argparse.ArgumentParser(description='Grader for the Going in Circles problem')
parser.add_argument('-t', dest='test_case', metavar='test_case', default="1")
parser.add_argument('program', nargs='+', help='Invocation of your solution')

args = parser.parse_args()
test_case = int(args.test_case)
assert 1 <= test_case <= 203, f'Test Case {test_case} must be between 1 and 203.'

with open(glob.glob(f'data/secret/{test_case:03}-*.in')[0], 'r') as fin:
    sequence = fin.read().split()[1]

sequence = list(sequence)
for c in sequence:
    assert c in '01', f'Character {c} may not appear in the input sequence.'

n = len(sequence)
position = 0

queries = 0
queries_limit = 3 * n + 500

with subprocess.Popen(" ".join(args.program),
                      shell=True,
                      stdout=subprocess.PIPE,
                      stdin=subprocess.PIPE,
                      universal_newlines=True) as p:
    try:
        write(p, sequence[position])

        while True:
            response = read(p)

            if response.startswith('? '):
                if queries == 50000:
                    wrong_answer(p, 'Program used too many queries, aborting')
                    break

                queries += 1
                action = response[2:]

                if action == 'right':
                    position = (position + 1) % n

                elif action == 'left':
                    position = (position - 1) % n

                elif action == 'flip':
                    sequence[position] = str(1 - int(sequence[position]))

                else:
                    wrong_answer(p, 'Program gave unrecognized action')

            elif response.startswith('! '):
                answer = response[2:]
                assert answer.isnumeric(), 'Expected final guess to be a positive integer'
                answer = int(answer)

                if answer == n:
                    assert queries <= queries_limit, 'Program printed correct solution, but used too many queries'
                    assert p.stdout.readline() == '', 'Printed extra data after finding solution'
                    assert p.wait() == 0, 'Did not exit cleanly after finishing'
                    break

                else:
                    wrong_answer(p, 'Program printed incorrect solution')
                    break

            else:
                wrong_answer(p, 'Program gave invalid response')
                break

            write(p, sequence[position])

    except:
        traceback.print_exc()

    finally:
        sys.stdout.flush()
        sys.stderr.flush()
        if DEBUG:
            sys.stdout.write(f'Used {queries} queries, limit is {queries_limit}.\n')
            sys.stdout.write('Program exit code: {p.wait()}\n')
        sys.stdout.write(f'Passed test case {test_case}\n')
        sys.stdout.flush()
