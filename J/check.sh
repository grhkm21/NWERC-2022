g++-11 -O2 J.cpp -o J
for i in $(seq -w 1 125); do
	./J < $(ls ./data/secret/$i-*.in) > j.out
	python3 -c "import glob; \
		f1 = open(glob.glob('./data/secret/$i-*.ans')[0]).read(); \
		f2 = open('j.out').read(); \
		assert(f1.strip().split() == f2.strip().split()); \
		print('Passed test case $i')
	"
done
