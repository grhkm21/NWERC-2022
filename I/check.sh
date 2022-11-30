for i in $(seq -w 1 71); do
	python3 I.py < $(ls ./data/secret/$i-*.in) > i.out
	python3 -c "import glob; \
		f1 = open(glob.glob('./data/secret/$i-*.in')[0]).read().strip().split('\n'); \
		f2 = open('i.out').read(); \
		a, b = map(int, f1[0].split()); \
		x, y = map(int, f2.split()); \
		seq = [str(t) if (t % x != 0 and t % y != 0) else (('Fizz' if t % x == 0 else '') + ('Buzz' if t % y == 0 else '')) for t in range(a, b + 1)]; \
		s1 = ' '.join(seq); \
		s2 = f1[1].strip(); \
		assert s1 == s2, f'{s1} != {s2}'; \
		print('Passed test case $i')
	"
done
