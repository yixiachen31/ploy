.PHONY = clean

# 目录(别动！)
SRC_DIR		:=	src
LIB_DIR		:=	lib
OUT_DIR		:=	out

# 源文件(可以自行添加文件)
SRC_SOURCE	:=	main.c tran_table.c action_func.c

# 文件(别动！)
OUT_FILE		:= $(addprefix $(OUT_DIR)/, a.out)
OUT_DEPENDENCY	:= $(addprefix $(LIB_DIR)/, $(patsubst %.c,%.o,$(SRC_SOURCE)))

# 常用makefile函数
# $(addprefix <prefix>,<names...>)
# $(patsubst <pattern>,<replacement>,<text>)

$(OUT_FILE): $(OUT_DEPENDENCY)
	mkdir -p $(OUT_DIR)
	gcc $^ -o $@

$(LIB_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(LIB_DIR)
	gcc -c $^ -o $@

clean:
	rm -rf $(LIB_DIR) $(OUT_DIR)
