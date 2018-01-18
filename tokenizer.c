#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"

/* Tokens regex */
static const char *at_token = "^@[[:alnum:]]";
static const char *at_num_token = "^@[[:digit:]]";
static const char *at_var_token = "^@[[:lower:]]";
static const char *label_token = "^\([A-Z]*\)";
static const char *comp_dest_token = "^[[:upper:]]=[[:alnum:]]";
static const char *comp_jmp_token = "^[[:alnum:]];[[:upper:]]";
static const char *space = "^[[:space:]]";


int is_space(const char *str) {
    return check_match(str, space);
}

static int is_label(const char *str) {
    return check_match(str, label_token);
}

static int is_AIns(const char *str) {
    return check_match(str, at_token);
}

static int is_CIns(const char *str) {
    return check_match(str, comp_dest_token) || check_match(str, comp_jmp_token);
}

void init_tokenizing(const char *buf, char *token, int *tok_type, C *c_inst, int state) {
    char *inst[2];

    if (is_CIns(buf) && state == pass2) {
        if (check_match(buf, comp_dest_token)) {
            inst[0] = strtok(buf, "=");
            inst[1] = strtok(NULL, "=");
            c_inst->dest = inst[0];
            c_inst->comp = inst[1];
        } else {
            inst[0] = strtok(buf, ";");
            inst[1] = strtok(NULL, ";");
            c_inst->comp = inst[0];
            c_inst->jmp = inst[1];
        }

        *tok_type = C_INS;
    } else if (is_label(buf)) {
        // (LOOP)
        int i = 0;
        while (*(++buf) != ')')
            token[i++] = *buf;
        *tok_type = LABEL;
    } else if (is_AIns(buf)) {
        // split with @
        inst[0] = strtok(buf, "@");

        if (check_match(buf, at_num_token))
            *tok_type = (state == pass2) ? NUMBER : -1;
        else if (check_match(buf, at_var_token))
            // if it's var(@i)
            *tok_type = A_INS;
        else
            // if it's label(@LOOP) operand
            *tok_type = (state == pass2) ? A_INS : -1;


        strcpy(token, inst[0]);
    }
}


static int check_match(const char *str, const char *rgx) {
    regex_t regex;
    int rets;
    char msgbuf[100];

    if (regcomp(&regex, rgx, 0)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    rets = regexec(&regex, str, 0, NULL, 0);

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    switch (rets) {
        case 0:
            return 1;
        case REG_NOMATCH:
            fprintf(stderr, "No match");
            break;
        default:
            regerror(rets, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            break;
    }
    return 0;
}