res_SRCS := $(wildcard $(DIR)/iso-*.blend)
res_OUT := $(res_SRCS:$(DIR)/iso-%.blend=$(DIR)/%.png)

res_all: $(res_OUT)

$(DIR)/%.png: $(DIR)/iso-%.blend
	blender -b $^ -o /tmp/ -a >/dev/null
	$(DIR)/merge-sprites.sh $@ /tmp/s0*.png
	convert $@ -depth 4 $@

res_clean:

res_distclean: res_clean
	rm -rf $(res_OUT)
