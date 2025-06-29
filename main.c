
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000
#define MAX_VARIABLES 100
#define MAX_VAR_NAME 50
#define MAX_BLAGUES 300

// Structure pour stocker les variables
typedef struct {
    char name[MAX_VAR_NAME];
    int value;
    char text_value[MAX_LINE_LENGTH];
    int is_number;
} Variable;

Variable variables[MAX_VARIABLES];
int var_count = 0;

// Base de données de blagues
const char* blagues[MAX_BLAGUES] = {
    "Pourquoi les plongeurs plongent-ils toujours en arrière et jamais en avant ? Parce que sinon, ils tombent dans le bateau !",
    "Que dit un escargot quand il croise une limace ? Regarde le nudiste !",
    "Qu'est-ce qui est jaune et qui attend ? Jonathan !",
    "Comment appelle-t-on un chat tombé dans un pot de peinture le jour de Noël ? Un chat-mallow !",
    "Qu'est-ce qui est transparent et qui sent la carotte ? Un pet de lapin !",
    "Pourquoi les poissons n'aiment pas jouer au tennis ? Parce qu'ils ont peur du filet !",
    "Qu'est-ce qui est petit, vert et qui monte et qui descend ? Un petit pois dans un ascenseur !",
    "Comment appelle-t-on un boomerang qui ne revient pas ? Un bâton !",
    "Qu'est-ce qui a 4 pattes le matin, 2 à midi et 3 le soir ? L'homme qui se casse une jambe !",
    "Pourquoi les dinosaures ne parlent pas ? Parce qu'ils sont morts !",
    // Ajouter plus de blagues...
    "Qu'est-ce qui est rouge et qui sent la peinture rouge ? De la peinture rouge !",
    "Comment fait-on pour allumer un barbecue breton ? On utilise des breizh !",
    "Qu'est-ce qui est blanc et qui ne sert à rien ? Un bonhomme de neige au soleil !",
    "Pourquoi les pêcheurs ne sont jamais gros ? Parce qu'ils surveillent leur ligne !",
    "Qu'est-ce qui est dur, blanc, avec le bout rouge ? Une cigarette à l'envers !"
};
const int nombre_blagues = 15; // Pour l'exemple, on n'a que 15 blagues

// Codes couleur ANSI
void print_color(const char* color, const char* message) {
    if (strcmp(color, "rouge") == 0) {
        printf("\033[31m%s\033[0m\n", message);
    } else if (strcmp(color, "vert") == 0) {
        printf("\033[32m%s\033[0m\n", message);
    } else if (strcmp(color, "bleu") == 0) {
        printf("\033[34m%s\033[0m\n", message);
    } else if (strcmp(color, "jaune") == 0) {
        printf("\033[33m%s\033[0m\n", message);
    } else if (strcmp(color, "rose") == 0) {
        printf("\033[35m%s\033[0m\n", message);
    } else if (strcmp(color, "cyan") == 0) {
        printf("\033[36m%s\033[0m\n", message);
    } else if (strcmp(color, "blanc") == 0) {
        printf("\033[37m%s\033[0m\n", message);
    } else {
        printf("%s\n", message);
    }
}

// Fonction pour trim les espaces
char* trim(char* str) {
    char* end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}

// Fonction pour trouver une variable
Variable* find_variable(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return &variables[i];
        }
    }
    return NULL;
}

// Fonction pour définir une variable
void set_variable(const char* name, int value, const char* text_value, int is_number) {
    Variable* var = find_variable(name);
    if (var == NULL) {
        if (var_count < MAX_VARIABLES) {
            var = &variables[var_count++];
            strcpy(var->name, name);
        } else {
            printf("Erreur: trop de variables définies!\n");
            return;
        }
    }
    var->value = value;
    if (text_value) {
        strcpy(var->text_value, text_value);
    }
    var->is_number = is_number;
}

// Fonction pour évaluer une expression mathématique simple
int evaluate_math(const char* expression) {
    char expr[MAX_LINE_LENGTH];
    strcpy(expr, expression);
    
    // Trouve l'opérateur
    char* op_pos = NULL;
    char op = 0;
    
    if ((op_pos = strchr(expr, '+')) != NULL) {
        op = '+';
    } else if ((op_pos = strchr(expr, '-')) != NULL) {
        op = '-';
    } else if ((op_pos = strchr(expr, '*')) != NULL) {
        op = '*';
    } else if ((op_pos = strchr(expr, '/')) != NULL) {
        op = '/';
    }
    
    if (op_pos == NULL) {
        return atoi(expr);
    }
    
    *op_pos = '\0';
    int left = atoi(trim(expr));
    int right = atoi(trim(op_pos + 1));
    
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return right != 0 ? left / right : 0;
        default: return 0;
    }
}

// Fonction pour traiter les commandes Wsh
void process_wsh(const char* message) {
    // Enlever les guillemets si présents
    char clean_message[MAX_LINE_LENGTH];
    strcpy(clean_message, message);
    
    if (clean_message[0] == '"' && clean_message[strlen(clean_message)-1] == '"') {
        clean_message[strlen(clean_message)-1] = '\0';
        memmove(clean_message, clean_message + 1, strlen(clean_message));
    }
    
    printf("%s\n", clean_message);
}

// Fonction pour traiter les commandes Capté (mathématiques)
void process_capte(const char* expression) {
    int result = evaluate_math(expression);
    printf("%d\n", result);
}

// Fonction pour traiter quoicoubeh (blagues)
void process_quoicoubeh(const char* command) {
    if (strstr(command, "donne moi ma blague poto ou tes mort") != NULL) {
        srand(time(NULL));
        int index = rand() % nombre_blagues;
        printf("🤣 %s\n", blagues[index]);
    } else {
        printf("Erreur: Tu dois écrire exactement 'quoicoubeh × donne moi ma blague poto ou tes mort' !\n");
    }
}

// Fonction pour traiter poto (conditions et variables)
void process_poto(const char* condition) {
    // Implémentation simplifiée pour les conditions
    printf("Condition poto traitée: %s\n", condition);
}

// Fonction pour traiter watt (définition de variables)
void process_watt(const char* definition) {
    char var_name[MAX_VAR_NAME];
    char value_str[MAX_LINE_LENGTH];
    
    // Parser "variable = valeur"
    if (sscanf(definition, "%s = %[^\n]", var_name, value_str) == 2) {
        // Vérifier si c'est un nombre ou du texte
        if (isdigit(value_str[0]) || (value_str[0] == '-' && isdigit(value_str[1]))) {
            int value = atoi(value_str);
            set_variable(var_name, value, NULL, 1);
            printf("Variable '%s' définie avec la valeur %d\n", var_name, value);
        } else {
            set_variable(var_name, 0, value_str, 0);
            printf("Variable '%s' définie avec la valeur '%s'\n", var_name, value_str);
        }
    }
}

// Fonction pour traiter reuf (couleurs)
void process_reuf(const char* command) {
    char color[50];
    char message[MAX_LINE_LENGTH];
    
    // Parser "couleur X - message"
    if (sscanf(command, "couleur %s - \"%[^\"]\"", color, message) == 2) {
        print_color(color, message);
    } else if (sscanf(command, "couleur %s - %[^\n]", color, message) == 2) {
        print_color(color, message);
    } else {
        printf("Erreur de syntaxe reuf!\n");
    }
}

// Fonction pour traiter Cité (délais)
void process_cite(const char* command) {
    int ms;
    if (sscanf(command, "%d ms", &ms) == 1) {
        printf("Délai de %d ms...\n", ms);
        usleep(ms * 1000); // convertir ms en microseconds
        printf("Délai terminé!\n");
    }
}

// Fonction pour traiter crampté (modification de message)
void process_crampte(const char* command) {
    char initial[MAX_LINE_LENGTH];
    char final[MAX_LINE_LENGTH];
    int ms;
    
    if (sscanf(command, "\"%[^\"]\", %d ms , \"%[^\"]\"", initial, &ms, final) == 3) {
        printf("%s", initial);
        fflush(stdout);
        usleep(ms * 1000);
        printf("\r%s\n", final);
    }
}

// Fonction principale pour traiter une ligne
void process_line(char* line) {
    char* trimmed = trim(line);
    
    if (trimmed[0] != '^') {
        return; // Ignorer les lignes qui ne commencent pas par ^
    }
    
    char* command = trimmed + 1; // Enlever le ^
    command = trim(command);
    
    if (strncmp(command, "Wsh -", 5) == 0) {
        process_wsh(command + 5);
    } else if (strncmp(command, "Capté :", 7) == 0) {
        process_capte(command + 7);
    } else if (strncmp(command, "quoicoubeh", 10) == 0) {
        process_quoicoubeh(command + 10);
    } else if (strncmp(command, "poto :", 6) == 0) {
        process_poto(command + 6);
    } else if (strncmp(command, "watt :", 6) == 0) {
        process_watt(command + 6);
    } else if (strncmp(command, "reuf :", 6) == 0) {
        process_reuf(command + 6);
    } else if (strncmp(command, "Cité -", 6) == 0) {
        process_cite(command + 6);
    } else if (strncmp(command, "crampté -", 9) == 0) {
        process_crampte(command + 9);
    } else {
        printf("Commande inconnue: %s\n", command);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3 || strcmp(argv[1], "wsh") != 0) {
        printf("Usage: %s wsh <fichier.wsh>\n", argv[0]);
        return 1;
    }
    
    FILE* file = fopen(argv[2], "r");
    if (file == NULL) {
        printf("Erreur: impossible d'ouvrir le fichier %s\n", argv[2]);
        return 1;
    }
    
    printf("🔥 Exécution du programme Wesh: %s 🔥\n\n", argv[2]);
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // Enlever le retour à la ligne
        line[strcspn(line, "\n")] = 0;
        process_line(line);
    }
    
    fclose(file);
    printf("\n🎯 Programme Wesh terminé! 🎯\n");
    return 0;
}
