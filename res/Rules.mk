res_SRCS := $(wildcard $(DIR)/iso-*.blend)
res_OUT := $(res_SRCS:$(DIR)/iso-%.blend=$(DIR)/%.png)

res_all: $(res_OUT)

$(DIR)/%.png: $(DIR)/iso-%.blend
	blender -b $^ -a >/dev/null
	$(DIR)/merge-sprites.sh $@ /tmp/s0*
