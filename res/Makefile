SRCS := $(wildcard iso-*.blend)
OUT := $(SRCS:iso-%.blend=%.png)

all: $(OUT)

%.png: iso-%.blend
	blender -b $^ -a >/dev/null
	./merge-sprites.sh $@ /tmp/s0*
