SERVER_NAME = server
CLIENT_NAME = client

CXX = c++
CXXFLAGS = -g -Wall -Werror -Wextra -fsanitize=address

SRCS_DIR = ./src
OBJS_DIR = ./obj

SERVER_SRCS = Server.cpp \
			  Selector.cpp \
			  main.cpp \
			  Request.cpp \
			  $(NULL)


SERVER_OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SERVER_SRCS:.cpp=.o)))

CLIENT_SRCS = TCPEchoClient.cpp \
			  DieWithError.cpp \
			  $(NULL)

CLIENT_OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(CLIENT_SRCS:.cpp=.o)))

DEPS = $(SERVER_OBJS:%.o=%.d) $(CLIENT_OBJS:%.o=%.d)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

.PHONY: all
all: $(OBJS_DIR) $(SERVER_NAME) $(CLIENT_NAME)

-include $(DEPS)

$(OBJS_DIR):
	mkdir $@

$(SERVER_NAME): $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) $(SERVER_OBJS) -o $@

$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) $(CLIENT_OBJS) -o $@

.PHONY: clean
clean:
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS) $(DEPS)

.PHONY: fclean
fclean: clean
	$(RM) $(SERVER_NAME)
	$(RM) $(CLIENT_NAME)

.PHONY: re
re: fclean all

.PHONY: lint
LINT_TARGET = $(shell find src -type f \( -name '*.cpp' -o -name '*.hpp' \))
lint:
	@cpplint --filter=-build/include_subdir,-legal/copyright \
			$(LINT_TARGET) > /dev/null
	@echo "$(GREEN)Pass cpplint:)$(END)"
	@clang-tidy $(LINT_TARGET) -- $(CXXFLAGS)
	@echo "$(GREEN)Pass clang-tidy:)$(END)"
	@echo "$(GREEN)Wao, What a clean code:)$(END)"

## Color
END		= \e[0m
BOLD	= \e[1m
THIN	= \e[2m
ITALIC	= \e[3m
U_LINE	= \e[4m
BLACK	= \e[30m
RED		= \e[31m
GREEN	= \e[32m
YELLOW	= \e[33m
BLUE	= \e[34m
PURPLE	= \e[35m
CYAN	= \e[36m
WHITE	= \e[37m
