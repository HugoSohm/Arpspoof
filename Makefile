##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Made by Hugo SOHM
##

NAME		=	myARPspoof

SRCS    	=	src/arp.c	\
				src/init.c	\
				src/if.c	\
				src/ipv4.c	\
				src/tools.c	\
				src/arpspoofing.c

OBJS		=	$(SRCS:.c=.o)
INCL		=	-Iinclude

####################################################

CC			=	gcc
RM			=	rm -f
CFLAGS		=	-W

#####################################################

.c.o	:
	@$(CC) $(CFLAGS) $(INCL) -c $< -o $@
	@printf " \033[34m[Compilation]\033[39m %s\n" $<

all	:	$(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@printf "\n \033[33m[Message]\033[39m ARPspoof compilation done\n"

clean	:
	@$(RM) *~ $(OBJS)
	@printf " \033[31m[Delete] \033[39m%s\n" $(OBJS)

fclean	:	clean
	@$(RM) $(NAME)
	@printf "\n \033[31m[Delete] \033[39m%s\n\n" $(NAME)

re	:	fclean all
