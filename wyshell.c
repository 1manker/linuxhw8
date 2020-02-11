/*************************************
 * wyshell.c
 * Author: Lucas Manker
 * Date: 10 April 2020
 *
 * scanner for 3750 wyshell project.
 * Parts of this code graciously provided by Dr. Buckner
 ************************************/

#include<stdio.h>
#include"wyscanner.h"


int main()
{
  char *tokens[]={ "QUOTE_ERROR", "ERROR_CHAR", "SYSTEM_ERROR",
                "EOL", "REDIR_OUT", "REDIR_IN", "APPEND_OUT",
                "REDIR_ERR", "APPEND_ERR", "REDIR_ERR_OUT", "SEMICOLON",
                "PIPE", "AMP", "WORD" };
  int rtn;
  char *rpt;
  char buf[1024];
  char *start = ":--:";
  char *inner = " --:";
  int command = 0;

  while(1) {
    printf("$>");
    rpt=fgets(buf,256,stdin);
    if(rpt == NULL) {
      if(feof(stdin)) {
	return 0;
      }
      else {
	perror("fgets from stdin");
	return 1;
      }
    }
    rtn=parse_line(buf);
    while(rtn !=  EOL){ 
      // that makes it break out when an error or EOL is seen
      switch(rtn) {
        case WORD:
          if(!command){
            printf("%s %s\n",start,lexeme);
            command = 1;
          }
          else{
              printf("%s %s\n",inner,lexeme);
          }
          break;
        case SEMICOLON:
          printf(" ;\n");
          command = 0;
          break;
        case PIPE:
          printf(" |\n");
          command = 0;
          break;
        case ERROR_CHAR:
          printf("%d: %s\t =%d\n",rtn,tokens[rtn%96],error_char);
          break;
        default:
          printf("%d: %s\n",rtn,tokens[rtn%96]);
      }
      rtn=parse_line(NULL);
    }
    if(rtn == EOL){
        printf("%s EOL", inner);
        command = 0;
    }
    printf("\n");
  }
}

