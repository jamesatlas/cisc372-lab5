CC := gcc
CFLAGS := -fopenmp
SRUN := GOMP_CPU_AFFINITY=1-16 srun

.PHONY: clean

%.out:
	$(CC) $(CFLAGS) -o $@ $(subst .out,,$@).c -lm

%-run-part1: clean
	$(MAKE) $(subst -run-part1,,$@).out
	$(SRUN) -c 2 $(subst -run-part1,,$@).out 20000 1
	$(SRUN) -c 4 $(subst -run-part1,,$@).out 20000 2
	$(SRUN) -c 8 $(subst -run-part1,,$@).out 20000 4
	$(SRUN) -c 16 $(subst -run-part1,,$@).out 20000 8

%-run-part2: clean
	$(MAKE) $(subst -run-part2,,$@).out
	$(SRUN) -c 2 $(subst -run-part2,,$@).out 1000000000 10 1
	$(SRUN) -c 4 $(subst -run-part2,,$@).out 1000000000 10 2
	$(SRUN) -c 8 $(subst -run-part2,,$@).out 1000000000 10 4
	$(SRUN) -c 16 $(subst -run-part2,,$@).out 1000000000 10 8

%-run-part3: clean
	$(MAKE) $(subst -run-part3,,$@).out
	$(SRUN) -c 2 $(subst -run-part3,,$@).out 16777216 1
	$(SRUN) -c 4 $(subst -run-part3,,$@).out 16777216 2
	$(SRUN) -c 8 $(subst -run-part3,,$@).out 16777216 4
	$(SRUN) -c 16 $(subst -run-part3,,$@).out 16777216 8

%-run-part4: clean
	$(MAKE) $(subst -run-part4,,$@).out
	$(SRUN) -c 2 $(subst -run-part4,,$@).out 1 10000000 1
	$(SRUN) -c 4 $(subst -run-part4,,$@).out 1 10000000 2
	$(SRUN) -c 8 $(subst -run-part4,,$@).out 1 10000000 4
	$(SRUN) -c 16 $(subst -run-part4,,$@).out 1 10000000 8

clean:
	$(RM) *.out
