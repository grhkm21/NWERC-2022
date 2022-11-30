g++-11 -o G G.cpp
for i in $(seq -w 1 203); do
	python3 validator.py -t $i "./G"
done
