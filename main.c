
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include <sys/stat.h>

#define MAX_LINE_LENGTH 1000
#define MAX_VARIABLES 100
#define MAX_VAR_NAME 50
#define MAX_BLAGUES 400
#define MAX_ARRAY_SIZE 100
#define MAX_FUNCTIONS 20
#define MAX_LOOPS 10
#define MAX_MODULES 10

// Structure pour stocker les variables
typedef struct {
    char name[MAX_VAR_NAME];
    int value;
    double float_value;
    char text_value[MAX_LINE_LENGTH];
    int is_number;
    int is_float;
    int is_array;
    int array_values[MAX_ARRAY_SIZE];
    int array_size;
} Variable;

// Structure pour les fonctions
typedef struct {
    char name[MAX_VAR_NAME];
    char body[MAX_LINE_LENGTH * 10];
    int param_count;
    char params[5][MAX_VAR_NAME];
} Function;

// Structure pour les boucles
typedef struct {
    int type; // 0 = while, 1 = for
    int active;
    int current_iteration;
    int max_iterations;
    char condition[MAX_LINE_LENGTH];
    char variable[MAX_VAR_NAME];
    int start_value;
    int end_value;
    long file_position;
    int loop_counter; // Compteur pour éviter les boucles infinies
} Loop;

// Structure pour les modules
typedef struct {
    char name[MAX_VAR_NAME];
    char path[MAX_LINE_LENGTH];
    int loaded;
} Module;

Variable variables[MAX_VARIABLES];
Function functions[MAX_FUNCTIONS];
Loop loops[MAX_LOOPS];
Module modules[MAX_MODULES];
int var_count = 0;
int func_count = 0;
int loop_count = 0;
int module_count = 0;
int current_loop = -1;

// Base de données de blagues étendues
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
    "Qu'est-ce qui est rouge et qui sent la peinture rouge ? De la peinture rouge !",
    "Comment fait-on pour allumer un barbecue breton ? On utilise des breizh !",
    "Qu'est-ce qui est blanc et qui ne sert à rien ? Un bonhomme de neige au soleil !",
    "Pourquoi les pêcheurs ne sont jamais gros ? Parce qu'ils surveillent leur ligne !",
    "Qu'est-ce qui est dur, blanc, avec le bout rouge ? Une cigarette à l'envers !",
    "Que dit un pingouin quand il mange ? C'est de la glace !",
    "Pourquoi les schtroumpfs rigolent tout le temps ? Parce qu'ils sont bleus !",
    "Comment appelle-t-on un chien qui n'a pas de pattes ? On ne l'appelle pas, on va le chercher !",
    "Que dit un cannibale quand il présente sa femme ? Ma chérie !",
    "Pourquoi les policiers portent des bretelles ? Pour tenir leur pantalon !",
    "Qu'est-ce qui est petit, rond et qui fait peur aux mammouths ? Un petit pois avec une kalach !",
    "Comment faire rire un squelette ? Il faut lui chatouiller les côtes !",
    "Pourquoi les poules pondent des œufs ? Parce que si elles les lançaient, ça casserait !",
    "Qu'est-ce qui est blanc et qui ne sert à rien dans un frigo ? Un bonhomme de neige !",
    "Que dit un paresseux dans un hamac ? Accroche-toi bien !",
    "Pourquoi les manchots ne volent pas ? Parce qu'ils n'ont pas de billet !",
    "Qu'est-ce qui est jaune et qui court vite ? Un citron pressé !",
    "Comment appelle-t-on un rat qui s'écrit avec un K ? Un rat-K !",
    "Que dit un aveugle dans un magasin de boules de pétanque ? Qui c'est qui crie comme ça ?",
    "Pourquoi les footballeurs ne jouent jamais au poker ? Parce qu'ils ont peur du carton !",
    "Qu'est-ce qui est noir et blanc et rouge partout ? Un journal !",
    "Comment fait-on pour attraper un lapin unique ? Unique up on it !",
    "Que dit un vampire végétarien ? Je veux sucer du raisin !",
    "Pourquoi les fourmis ne vont jamais à l'église ? Parce qu'elles sont in-sectes !",
    "Qu'est-ce qui a des dents mais ne mange jamais ? Un peigne !",
    "Que dit un mec qui tombe dans l'eau ? J'ai coulé !",
    "Pourquoi les clowns n'ouvrent jamais de restaurant ? Parce qu'ils font toujours le clown !",
    "Qu'est-ce qui monte mais ne descend jamais ? L'âge !",
    "Comment appelle-t-on un chat qui mange avec les pieds ? Un chat-mal-poli !",
    "Que dit un pêcheur qui ne prend rien ? Ça mord pas !",
    "Pourquoi Superman porte un slip par-dessus son pantalon ? Parce que sinon on ne verrait pas qu'il en porte un !",
    "C'est l'histoire d'un mec qui rentre dans un café... PLOUF !",
    "Qu'est-ce qui est blanc et qui tombe du haut ? Une avalanche de dents !",
    "Pourquoi les mexicains mangent épicé ? Pour avoir chaud au ventre quand il fait froid !",
    "Qu'est-ce qui est jaune et qui fait coin-coin ? Un canard qui a la jaunisse !",
    "Comment appelle-t-on un homme sans bras et sans jambes ? On ne l'appelle pas, on va le chercher !",
    "Que dit un cannibale quand il n'a plus faim ? J'en ai ras le bol !",
    "C'est quoi la différence entre un pigeon ? Ses deux pattes sont pareilles, surtout la gauche !",
    "Pourquoi les plongeurs plongent-ils en arrière ? Parce que sinon ils restent dans le bateau !",
    "Qu'est-ce qui est rouge et invisible ? Pas de tomates !",
    "Comment appelle-t-on un chat qui a bu trop de lait ? Un chat-mallow !",
    "Qu'est-ce qui a 4 roues et des mouches ? Une poubelle !",
    "Pourquoi les poissons n'ont pas d'argent ? Parce que c'est pas leur monnaie !",
    "Qu'est-ce qui est petit, vert et qui rit ? Un petit pois qui regarde un navet se déshabiller !",
    "Comment fait-on pour énerver un archéologue ? On lui donne un os à ronger !",
    "Que dit un serpent quand on lui marche dessus ? Aïe-Python !",
    "Pourquoi les abeilles ont-elles les cheveux collants ? Parce qu'elles utilisent des honey-combs !",
    "Qu'est-ce qui a des dents mais ne mord jamais ? Une fermeture éclair !",
    "Comment appelle-t-on un taureau qui fait de la peinture ? Un taureau-pinceau !",
    "Que dit un escargot quand il fait de l'auto-stop ? Es-cargo !",
    "Pourquoi les fantômes ne mentent jamais ? Parce qu'on peut voir à travers eux !",
    "Qu'est-ce qui a un lit mais ne dort jamais ? Une rivière !",
    "Comment appelle-t-on un poisson qui surveille la pharmacie ? Un gardon !",
    "Qu'est-ce qui est invisible et qui sent le haricot ? Un pet de lapin invisible !",
    "Pourquoi les mathématiciens ne bronzent jamais ? Parce qu'ils évitent les rayons !",
    "Qu'est-ce qui est petit, jaune et très dangereux ? Un poussin avec une mitraillette !",
    "Comment fait-on pour qu'un cyclope ferme les yeux ? On lui donne un coup de poing dans l'œil !",
    "Qu'est-ce qui est carré et qui fait de la musique ? Un dé qui chante !",
    "Pourquoi les sorcières volent-elles sur des balais ? Parce que l'aspirateur fait trop de bruit !",
    "Qu'est-ce qui a des feuilles mais n'est pas un arbre ? Un livre !",
    "Comment appelle-t-on un chat qui vit au pôle Nord ? Un chat-mallow gelé !",
    "Pourquoi les poissons rouges ne peuvent pas jouer au football ? Parce qu'ils se font avoir par les filets !",
    "Qu'est-ce qui court plus vite qu'un cheval ? Deux chevaux !",
    "Comment fait-on pour empêcher un taureau de charger ? On lui confisque sa carte bleue !",
    "Qu'est-ce qui est blanc le jour et noir la nuit ? Un zèbre qui travaille de nuit !",
    "Pourquoi les requins ne mangent pas de clowns ? Parce que ça a un goût de plastique !",
    "Qu'est-ce qui a des cornes mais ne fait pas de bruit ? Un escargot qui regarde un film muet !",
    "Comment appelle-t-on un homme qui a perdu 95% de son intelligence ? Un veuf !"
};
const int nombre_blagues = 71;

// Variables pour la gestion des conditions
int condition_result = 0;
int in_condition_block = 0;
int execute_then_block = 0;

// Variables globales pour l'état actuel
FILE* current_file = NULL;
int in_function_def = 0;
char current_function_name[MAX_VAR_NAME];
int debug_mode = 0;
int performance_mode = 0;

// Codes couleur ANSI améliorés
void print_color(const char* color, const char* message) {
    if (strcmp(color, "rouge") == 0 || strcmp(color, "red") == 0) {
        printf("\033[31m%s\033[0m\n", message);
    } else if (strcmp(color, "vert") == 0 || strcmp(color, "green") == 0) {
        printf("\033[32m%s\033[0m\n", message);
    } else if (strcmp(color, "bleu") == 0 || strcmp(color, "blue") == 0) {
        printf("\033[34m%s\033[0m\n", message);
    } else if (strcmp(color, "jaune") == 0 || strcmp(color, "yellow") == 0) {
        printf("\033[33m%s\033[0m\n", message);
    } else if (strcmp(color, "rose") == 0 || strcmp(color, "pink") == 0 || strcmp(color, "magenta") == 0) {
        printf("\033[35m%s\033[0m\n", message);
    } else if (strcmp(color, "cyan") == 0) {
        printf("\033[36m%s\033[0m\n", message);
    } else if (strcmp(color, "blanc") == 0 || strcmp(color, "white") == 0) {
        printf("\033[37m%s\033[0m\n", message);
    } else if (strcmp(color, "violet") == 0 || strcmp(color, "purple") == 0) {
        printf("\033[35m%s\033[0m\n", message);
    } else if (strcmp(color, "orange") == 0) {
        printf("\033[33m%s\033[0m\n", message);
    } else if (strcmp(color, "gris") == 0 || strcmp(color, "gray") == 0) {
        printf("\033[90m%s\033[0m\n", message);
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

// Fonction pour trouver une fonction
Function* find_function(const char* name) {
    for (int i = 0; i < func_count; i++) {
        if (strcmp(functions[i].name, name) == 0) {
            return &functions[i];
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
            var->is_array = 0;
            var->array_size = 0;
            var->is_float = 0;
        } else {
            printf("❌ Erreur: trop de variables définies mon poto!\n");
            return;
        }
    }
    var->value = value;
    if (text_value) {
        strcpy(var->text_value, text_value);
    }
    var->is_number = is_number;
}

// Fonction pour définir une variable float
void set_float_variable(const char* name, double value) {
    Variable* var = find_variable(name);
    if (var == NULL) {
        if (var_count < MAX_VARIABLES) {
            var = &variables[var_count++];
            strcpy(var->name, name);
            var->is_array = 0;
            var->array_size = 0;
        } else {
            printf("❌ Erreur: trop de variables définies mon poto!\n");
            return;
        }
    }
    var->float_value = value;
    var->is_float = 1;
    var->is_number = 1;
}

// Fonction pour définir un tableau
void set_array(const char* name, int* values, int size) {
    Variable* var = find_variable(name);
    if (var == NULL) {
        if (var_count < MAX_VARIABLES) {
            var = &variables[var_count++];
            strcpy(var->name, name);
        } else {
            printf("❌ Erreur: trop de variables définies mon poto!\n");
            return;
        }
    }
    var->is_array = 1;
    var->array_size = size;
    for (int i = 0; i < size && i < MAX_ARRAY_SIZE; i++) {
        var->array_values[i] = values[i];
    }
}

// Fonction pour évaluer une expression mathématique avancée
double evaluate_math_advanced(const char* expression) {
    char expr[MAX_LINE_LENGTH];
    strcpy(expr, expression);
    char* trimmed_expr = trim(expr);
    
    // Gestion des fonctions mathématiques
    if (strncmp(trimmed_expr, "sqrt(", 5) == 0) {
        char* end = strchr(trimmed_expr + 5, ')');
        if (end) {
            *end = '\0';
            double val = evaluate_math_advanced(trimmed_expr + 5);
            return sqrt(val);
        }
    }
    
    if (strncmp(trimmed_expr, "sin(", 4) == 0) {
        char* end = strchr(trimmed_expr + 4, ')');
        if (end) {
            *end = '\0';
            double val = evaluate_math_advanced(trimmed_expr + 4);
            return sin(val);
        }
    }
    
    if (strncmp(trimmed_expr, "cos(", 4) == 0) {
        char* end = strchr(trimmed_expr + 4, ')');
        if (end) {
            *end = '\0';
            double val = evaluate_math_advanced(trimmed_expr + 4);
            return cos(val);
        }
    }
    
    if (strncmp(trimmed_expr, "pow(", 4) == 0) {
        char* comma = strchr(trimmed_expr + 4, ',');
        char* end = strchr(trimmed_expr + 4, ')');
        if (comma && end) {
            *comma = '\0';
            *end = '\0';
            double base = evaluate_math_advanced(trimmed_expr + 4);
            double exp = evaluate_math_advanced(comma + 1);
            return pow(base, exp);
        }
    }
    
    // Trouve l'opérateur
    char* op_pos = NULL;
    char op = 0;
    
    // Chercher les opérateurs dans l'ordre de priorité
    if ((op_pos = strstr(trimmed_expr, " + ")) != NULL) {
        op = '+';
        op_pos += 1;
    } else if ((op_pos = strstr(trimmed_expr, " - ")) != NULL) {
        op = '-';
        op_pos += 1;
    } else if ((op_pos = strstr(trimmed_expr, " * ")) != NULL) {
        op = '*';
        op_pos += 1;
    } else if ((op_pos = strstr(trimmed_expr, " / ")) != NULL) {
        op = '/';
        op_pos += 1;
    } else if ((op_pos = strstr(trimmed_expr, " % ")) != NULL) {
        op = '%';
        op_pos += 1;
    }
    
    if (op_pos == NULL) {
        // Vérifier si c'est une variable
        Variable* var = find_variable(trimmed_expr);
        if (var && var->is_number) {
            return var->is_float ? var->float_value : (double)var->value;
        }
        return atof(trimmed_expr);
    }
    
    *op_pos = '\0';
    char* left_str = trim(expr);
    char* right_str = trim(op_pos + 1);
    
    double left, right;
    
    // Évaluer la partie gauche
    Variable* var_left = find_variable(left_str);
    if (var_left && var_left->is_number) {
        left = var_left->is_float ? var_left->float_value : (double)var_left->value;
    } else {
        left = atof(left_str);
    }
    
    // Évaluer la partie droite
    Variable* var_right = find_variable(right_str);
    if (var_right && var_right->is_number) {
        right = var_right->is_float ? var_right->float_value : (double)var_right->value;
    } else {
        right = atof(right_str);
    }
    
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return right != 0 ? left / right : 0;
        case '%': return fmod(left, right);
        default: return 0;
    }
}

// Fonction pour évaluer une expression mathématique simple (compatibilité)
int evaluate_math(const char* expression) {
    return (int)evaluate_math_advanced(expression);
}

// Fonction pour évaluer une condition
int evaluate_condition(const char* condition) {
    char cond[MAX_LINE_LENGTH];
    strcpy(cond, condition);
    char* trimmed_cond = trim(cond);
    
    // Chercher les opérateurs de comparaison
    char* op_pos = NULL;
    char op[3] = {0};
    
    if ((op_pos = strstr(trimmed_cond, " >= ")) != NULL) {
        strcpy(op, ">=");
        op_pos += 1;
    } else if ((op_pos = strstr(trimmed_cond, " <= ")) != NULL) {
        strcpy(op, "<=");
        op_pos += 1;
    } else if ((op_pos = strstr(trimmed_cond, " == ")) != NULL) {
        strcpy(op, "==");
        op_pos += 1;
    } else if ((op_pos = strstr(trimmed_cond, " != ")) != NULL) {
        strcpy(op, "!=");
        op_pos += 1;
    } else if ((op_pos = strstr(trimmed_cond, " > ")) != NULL) {
        strcpy(op, ">");
        op_pos += 1;
    } else if ((op_pos = strstr(trimmed_cond, " < ")) != NULL) {
        strcpy(op, "<");
        op_pos += 1;
    }
    
    if (op_pos == NULL) {
        return 0;
    }
    
    *op_pos = '\0';
    char* left_str = trim(cond);
    char* right_str = trim(op_pos + strlen(op));
    
    double left, right;
    
    // Évaluer la partie gauche
    Variable* var_left = find_variable(left_str);
    if (var_left && var_left->is_number) {
        left = var_left->is_float ? var_left->float_value : (double)var_left->value;
    } else {
        left = atof(left_str);
    }
    
    // Évaluer la partie droite
    Variable* var_right = find_variable(right_str);
    if (var_right && var_right->is_number) {
        right = var_right->is_float ? var_right->float_value : (double)var_right->value;
    } else {
        right = atof(right_str);
    }
    
    // Appliquer l'opérateur
    if (strcmp(op, ">") == 0) return left > right;
    if (strcmp(op, "<") == 0) return left < right;
    if (strcmp(op, ">=") == 0) return left >= right;
    if (strcmp(op, "<=") == 0) return left <= right;
    if (strcmp(op, "==") == 0) return fabs(left - right) < 0.0001; // Pour les flottants
    if (strcmp(op, "!=") == 0) return fabs(left - right) >= 0.0001;
    
    return 0;
}

void process_line(char* line); // Déclaration anticipée

// Fonction pour traiter les commandes Wsh
void process_wsh(const char* message) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    char clean_message[MAX_LINE_LENGTH];
    strcpy(clean_message, message);
    char* trimmed = trim(clean_message);
    
    if (strlen(trimmed) >= 2 && trimmed[0] == '"' && trimmed[strlen(trimmed)-1] == '"') {
        trimmed[strlen(trimmed)-1] = '\0';
        memmove(trimmed, trimmed + 1, strlen(trimmed));
    }
    
    printf("%s\n", trimmed);
}

// Fonction pour traiter les commandes Capté (mathématiques)
void process_capte(const char* expression) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    double result = evaluate_math_advanced(expression);
    if (result == (int)result) {
        printf("%d\n", (int)result);
    } else {
        printf("%.2f\n", result);
    }
}

// Fonction pour traiter quoicoubeh (blagues)
void process_quoicoubeh(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    char* trimmed_command = trim((char*)command);
    if (strstr(trimmed_command, "× donne moi ma blague poto ou tes mort") != NULL ||
        strstr(trimmed_command, "donne moi ma blague poto ou tes mort") != NULL) {
        static int seed_initialized = 0;
        if (!seed_initialized) {
            srand(time(NULL));
            seed_initialized = 1;
        }
        int index = rand() % nombre_blagues;
        printf("🤣 Voici une blague pour toi mon reuf:\n");
        printf("💬 %s\n", blagues[index]);
    } else {
        printf("❌ Erreur: Tu dois écrire exactement 'quoicoubeh × donne moi ma blague poto ou tes mort' !\n");
    }
}

// Fonction pour traiter poto (conditions et variables)
void process_poto(const char* condition) {
    char cond[MAX_LINE_LENGTH];
    strcpy(cond, condition);
    char* trimmed = trim(cond);
    
    if (strncmp(trimmed, "si ", 3) == 0) {
        in_condition_block = 1;
        condition_result = evaluate_condition(trimmed + 3);
        execute_then_block = condition_result;
        if (debug_mode) {
            printf("🔍 Debug: condition '%s' = %s\n", trimmed + 3, condition_result ? "vraie" : "fausse");
        }
    }
}

void process_alors() {
    // Cette fonction sera appelée quand on rencontre "alors"
}

// Fonction pour traiter watt (définition de variables)
void process_watt(const char* definition) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    char var_name[MAX_VAR_NAME];
    char value_str[MAX_LINE_LENGTH];
    
    if (sscanf(definition, "%s = %[^\n]", var_name, value_str) == 2) {
        char* trimmed_value = trim(value_str);
        
        // Vérifier si c'est un calcul mathématique
        if (strstr(trimmed_value, "+") || strstr(trimmed_value, "-") || 
            strstr(trimmed_value, "*") || strstr(trimmed_value, "/") ||
            strstr(trimmed_value, "sqrt") || strstr(trimmed_value, "sin") ||
            strstr(trimmed_value, "cos") || strstr(trimmed_value, "pow")) {
            double result = evaluate_math_advanced(trimmed_value);
            if (result == (int)result) {
                set_variable(var_name, (int)result, NULL, 1);
                printf("✅ Variable '%s' définie avec la valeur %d\n", var_name, (int)result);
            } else {
                set_float_variable(var_name, result);
                printf("✅ Variable '%s' définie avec la valeur %.2f\n", var_name, result);
            }
        } else if (strchr(trimmed_value, '.') != NULL && isdigit(trimmed_value[0])) {
            // Nombre décimal
            double value = atof(trimmed_value);
            set_float_variable(var_name, value);
            printf("✅ Variable '%s' définie avec la valeur %.2f\n", var_name, value);
        } else if (isdigit(trimmed_value[0]) || (trimmed_value[0] == '-' && isdigit(trimmed_value[1]))) {
            // Nombre entier
            int value = atoi(trimmed_value);
            set_variable(var_name, value, NULL, 1);
            printf("✅ Variable '%s' définie avec la valeur %d\n", var_name, value);
        } else {
            // Texte
            set_variable(var_name, 0, trimmed_value, 0);
            printf("✅ Variable '%s' définie avec la valeur %s\n", var_name, trimmed_value);
        }
    }
}

// Fonction pour traiter reuf (couleurs)
void process_reuf(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    char color[50];
    char message[MAX_LINE_LENGTH];
    char* trimmed_command = trim((char*)command);
    
    if (sscanf(trimmed_command, "couleur %s - \"%[^\"]\"", color, message) == 2) {
        print_color(color, message);
    } 
    else if (sscanf(trimmed_command, "couleur %s - %[^\n]", color, message) == 2) {
        char* clean_msg = trim(message);
        if (clean_msg[0] == '"' && clean_msg[strlen(clean_msg)-1] == '"') {
            clean_msg[strlen(clean_msg)-1] = '\0';
            clean_msg++;
        }
        print_color(color, clean_msg);
    } 
    else {
        printf("❌ Erreur de syntaxe reuf! Utilise: ^ reuf : couleur [couleur] - \"[message]\"\n");
        printf("🎨 Couleurs disponibles: rouge, vert, bleu, jaune, rose, cyan, blanc, violet, orange, gris\n");
    }
}

// Fonction pour traiter Cité (délais)
void process_cite(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    int ms;
    char* trimmed_command = trim((char*)command);
    
    if (sscanf(trimmed_command, "%d ms", &ms) == 1) {
        printf("⏱️  Attente de %d ms...", ms);
        fflush(stdout);
        usleep(ms * 1000);
        printf("\r⏱️  Attente de %d ms... ✅ Terminé!\n", ms);
        fflush(stdout);
    } else {
        printf("❌ Erreur: format incorrect pour Cité. Utilise: ^ Cité - [nombre] ms\n");
        printf("📝 Exemple: ^ Cité - 1000 ms\n");
        printf("🔍 Debug: commande reçue = '%s'\n", trimmed_command);
    }
}

// Fonction pour traiter crampté (modification de message)
void process_crampte(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    char initial[MAX_LINE_LENGTH];
    char final[MAX_LINE_LENGTH];
    int ms;
    
    char trimmed_command[MAX_LINE_LENGTH];
    strcpy(trimmed_command, command);
    char* cmd = trim(trimmed_command);
    
    // Parser plus flexible pour crampté
    if (sscanf(cmd, "\"%[^\"]\", %d ms, \"%[^\"]\"", initial, &ms, final) == 3 ||
        sscanf(cmd, "\"%[^\"]\", %d ms , \"%[^\"]\"", initial, &ms, final) == 3 ||
        sscanf(cmd, "\"%[^\"]\"%*[ ]*,%*[ ]*%d%*[ ]*ms%*[ ]*,%*[ ]*\"%[^\"]\"", initial, &ms, final) == 3) {
        
        printf("🔄 %s", initial);
        fflush(stdout);
        usleep(ms * 1000);
        
        // Effacement plus robuste
        printf("\r");
        for(int i = 0; i < 80; i++) {  // Effacer 80 caractères
            printf(" ");
        }
        printf("\r✅ %s\n", final);
        fflush(stdout);
    } else {
        printf("❌ Erreur de syntaxe crampté! Utilise: ^ crampté - \"message initial\", [délai] ms , \"message final\"\n");
        printf("📝 Exemple: ^ crampté - \"Chargement...\", 1000 ms , \"Terminé!\"\n");
        printf("🔍 Debug: commande reçue = '%s'\n", cmd);
    }
}

// NOUVELLES FONCTIONNALITÉS

// bogoss - Boucles while améliorées
void process_bogoss(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    char condition[MAX_LINE_LENGTH];
    if (sscanf(command, "tant que %[^\n]", condition) == 1) {
        if (loop_count < MAX_LOOPS) {
            loops[loop_count].type = 0; // while
            loops[loop_count].active = 1;
            loops[loop_count].loop_counter = 0; // Protection contre les boucles infinies
            strcpy(loops[loop_count].condition, condition);
            loops[loop_count].file_position = ftell(current_file);
            current_loop = loop_count;
            loop_count++;
            printf("🔄 Boucle while démarrée: %s\n", condition);
        }
    } else {
        printf("❌ Erreur bogoss! Utilise: ^ bogoss : tant que [condition]\n");
        printf("📝 Exemple: ^ bogoss : tant que x < 5\n");
    }
}

// gadjo - Boucles for améliorées
void process_gadjo(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    char var_name[MAX_VAR_NAME];
    int start, end;
    if (sscanf(command, "%s de %d à %d", var_name, &start, &end) == 3) {
        if (loop_count < MAX_LOOPS) {
            loops[loop_count].type = 1; // for
            loops[loop_count].active = 1;
            strcpy(loops[loop_count].variable, var_name);
            loops[loop_count].start_value = start;
            loops[loop_count].end_value = end;
            loops[loop_count].current_iteration = start;
            loops[loop_count].file_position = ftell(current_file);
            current_loop = loop_count;
            loop_count++;
            
            // Initialiser la variable de boucle
            set_variable(var_name, start, NULL, 1);
            printf("🔥 Boucle for démarrée: %s de %d à %d\n", var_name, start, end);
        }
    } else {
        printf("❌ Erreur gadjo! Utilise: ^ gadjo : [variable] de [début] à [fin]\n");
        printf("📝 Exemple: ^ gadjo : i de 1 à 10\n");
    }
}

// pélo - Tableaux/listes améliorés
void process_pelo(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    char array_name[MAX_VAR_NAME];
    char values_str[MAX_LINE_LENGTH];
    
    if (sscanf(command, "%s = [%[^]]", array_name, values_str) == 2) {
        int values[MAX_ARRAY_SIZE];
        int count = 0;
        char* token = strtok(values_str, ",");
        
        while (token != NULL && count < MAX_ARRAY_SIZE) {
            values[count] = atoi(trim(token));
            count++;
            token = strtok(NULL, ",");
        }
        
        set_array(array_name, values, count);
        printf("🔥 Tableau '%s' créé avec %d éléments\n", array_name, count);
    } else if (sscanf(command, "affiche %s", array_name) == 1) {
        Variable* var = find_variable(array_name);
        if (var && var->is_array) {
            printf("📋 Tableau %s: [", array_name);
            for (int i = 0; i < var->array_size; i++) {
                printf("%d", var->array_values[i]);
                if (i < var->array_size - 1) printf(", ");
            }
            printf("]\n");
        } else {
            printf("❌ Tableau '%s' introuvable mon poto!\n", array_name);
        }
    } else if (sscanf(command, "taille %s", array_name) == 1) {
        Variable* var = find_variable(array_name);
        if (var && var->is_array) {
            printf("📏 Tableau '%s' contient %d éléments\n", array_name, var->array_size);
        } else {
            printf("❌ Tableau '%s' introuvable mon poto!\n", array_name);
        }
    } else if (sscanf(command, "tri %s", array_name) == 1) {
        Variable* var = find_variable(array_name);
        if (var && var->is_array) {
            // Tri à bulles simple
            for (int i = 0; i < var->array_size - 1; i++) {
                for (int j = 0; j < var->array_size - i - 1; j++) {
                    if (var->array_values[j] > var->array_values[j + 1]) {
                        int temp = var->array_values[j];
                        var->array_values[j] = var->array_values[j + 1];
                        var->array_values[j + 1] = temp;
                    }
                }
            }
            printf("🔄 Tableau '%s' trié avec succès!\n", array_name);
        } else {
            printf("❌ Tableau '%s' introuvable mon poto!\n", array_name);
        }
    } else {
        printf("❌ Erreur pélo! Utilise: ^ pélo : [nom] = [val1, val2, val3], affiche [nom], taille [nom], ou tri [nom]\n");
        printf("📝 Exemple: ^ pélo : tab = [1, 2, 3, 4, 5]\n");
    }
}

// sah - Input utilisateur amélioré
void process_sah(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    char var_name[MAX_VAR_NAME];
    char prompt[MAX_LINE_LENGTH];
    
    if (sscanf(command, "\"%[^\"]\" dans %s", prompt, var_name) == 2) {
        printf("❓ %s ", prompt);
        fflush(stdout);
        
        char input[MAX_LINE_LENGTH];
        if (fgets(input, sizeof(input), stdin)) {
            input[strcspn(input, "\n")] = 0; // Enlever le \n
            
            if (strchr(input, '.') != NULL && atof(input) != 0) {
                // Nombre décimal
                set_float_variable(var_name, atof(input));
                printf("✅ Nombre décimal %.2f stocké dans '%s'\n", atof(input), var_name);
            } else if (isdigit(input[0]) || (input[0] == '-' && isdigit(input[1]))) {
                // Nombre entier
                set_variable(var_name, atoi(input), NULL, 1);
                printf("✅ Nombre %d stocké dans '%s'\n", atoi(input), var_name);
            } else {
                // Texte
                set_variable(var_name, 0, input, 0);
                printf("✅ Texte '%s' stocké dans '%s'\n", input, var_name);
            }
        }
    } else {
        printf("❌ Erreur sah! Utilise: ^ sah : \"[question]\" dans [variable]\n");
        printf("📝 Exemple: ^ sah : \"Quel est ton âge ?\" dans age\n");
    }
}

// wAllah - Assertions/vérifications améliorées
void process_wallah(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    char condition[MAX_LINE_LENGTH];
    char message[MAX_LINE_LENGTH];
    
    if (sscanf(command, "%[^,], \"%[^\"]\"", condition, message) == 2) {
        int result = evaluate_condition(trim(condition));
        if (result) {
            printf("✅ wAllah c'est vrai: %s\n", message);
        } else {
            printf("❌ wAllah c'est faux: %s\n", message);
        }
    } else {
        printf("❌ Erreur wAllah! Utilise: ^ wAllah : [condition], \"[message]\"\n");
        printf("📝 Exemple: ^ wAllah : age > 18, \"Tu es majeur!\"\n");
    }
}

// daronne - Fichiers I/O amélioré
void process_daronne(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    char filename[MAX_LINE_LENGTH];
    char content[MAX_LINE_LENGTH];
    
    if (sscanf(command, "écris \"%[^\"]\" dans \"%[^\"]\"", content, filename) == 2) {
        FILE* f = fopen(filename, "w");
        if (f) {
            fprintf(f, "%s\n", content);
            fclose(f);
            printf("✅ Écrit dans le fichier '%s': %s\n", filename, content);
        } else {
            printf("❌ Impossible d'écrire dans '%s' mon poto!\n", filename);
        }
    } else if (sscanf(command, "ajoute \"%[^\"]\" dans \"%[^\"]\"", content, filename) == 2) {
        FILE* f = fopen(filename, "a");
        if (f) {
            fprintf(f, "%s\n", content);
            fclose(f);
            printf("✅ Ajouté dans le fichier '%s': %s\n", filename, content);
        } else {
            printf("❌ Impossible d'ajouter dans '%s' mon poto!\n", filename);
        }
    } else if (sscanf(command, "lis \"%[^\"]\"", filename) == 1) {
        FILE* f = fopen(filename, "r");
        if (f) {
            printf("📖 Contenu de '%s':\n", filename);
            char line[MAX_LINE_LENGTH];
            while (fgets(line, sizeof(line), f)) {
                printf("   %s", line);
            }
            fclose(f);
        } else {
            printf("❌ Impossible de lire '%s' mon poto!\n", filename);
        }
    } else if (sscanf(command, "supprime \"%[^\"]\"", filename) == 1) {
        if (remove(filename) == 0) {
            printf("✅ Fichier '%s' supprimé avec succès!\n", filename);
        } else {
            printf("❌ Impossible de supprimer '%s' mon poto!\n", filename);
        }
    } else if (sscanf(command, "existe \"%[^\"]\"", filename) == 1) {
        struct stat st;
        if (stat(filename, &st) == 0) {
            printf("✅ Le fichier '%s' existe!\n", filename);
        } else {
            printf("❌ Le fichier '%s' n'existe pas!\n", filename);
        }
    } else {
        printf("❌ Erreur daronne! Utilise: écris, ajoute, lis, supprime, ou existe\n");
        printf("📝 Exemples:\n");
        printf("   ^ daronne : écris \"Salut\" dans \"test.txt\"\n");
        printf("   ^ daronne : ajoute \"Ligne\" dans \"test.txt\"\n");
        printf("   ^ daronne : lis \"test.txt\"\n");
        printf("   ^ daronne : supprime \"test.txt\"\n");
        printf("   ^ daronne : existe \"test.txt\"\n");
    }
}

// zonzon - Try/catch errors amélioré
void process_zonzon(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    printf("🚨 Zone de sécurité activée: %s\n", command);
    // Pour l'instant juste un message, on pourrait implémenter un vrai try/catch
}

// NOUVELLES FONCTIONNALITÉS AVANCÉES

// turfu - Fonctions mathématiques avancées
void process_turfu(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    char func_name[50];
    char params[MAX_LINE_LENGTH];
    
    if (sscanf(command, "%s(%[^)])", func_name, params) == 2) {
        double param = evaluate_math_advanced(params);
        double result = 0;
        
        if (strcmp(func_name, "sqrt") == 0) {
            result = sqrt(param);
        } else if (strcmp(func_name, "sin") == 0) {
            result = sin(param);
        } else if (strcmp(func_name, "cos") == 0) {
            result = cos(param);
        } else if (strcmp(func_name, "tan") == 0) {
            result = tan(param);
        } else if (strcmp(func_name, "log") == 0) {
            result = log(param);
        } else if (strcmp(func_name, "abs") == 0) {
            result = fabs(param);
        } else {
            printf("❌ Fonction '%s' inconnue mon reuf!\n", func_name);
            return;
        }
        
        printf("🧮 %s(%.2f) = %.4f\n", func_name, param, result);
    } else {
        printf("❌ Erreur turfu! Utilise: ^ turfu : [fonction]([paramètre])\n");
        printf("📝 Fonctions: sqrt, sin, cos, tan, log, abs\n");
    }
}

// teubé - Debug et informations système
void process_teube(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    char* trimmed = trim((char*)command);
    
    if (strcmp(trimmed, "debug on") == 0) {
        debug_mode = 1;
        printf("🔍 Mode debug activé!\n");
    } else if (strcmp(trimmed, "debug off") == 0) {
        debug_mode = 0;
        printf("🔍 Mode debug désactivé!\n");
    } else if (strcmp(trimmed, "variables") == 0) {
        printf("📊 Variables définies (%d/%d):\n", var_count, MAX_VARIABLES);
        for (int i = 0; i < var_count; i++) {
            if (variables[i].is_array) {
                printf("   %s = tableau[%d]\n", variables[i].name, variables[i].array_size);
            } else if (variables[i].is_float) {
                printf("   %s = %.2f (float)\n", variables[i].name, variables[i].float_value);
            } else if (variables[i].is_number) {
                printf("   %s = %d (int)\n", variables[i].name, variables[i].value);
            } else {
                printf("   %s = \"%s\" (text)\n", variables[i].name, variables[i].text_value);
            }
        }
    } else if (strcmp(trimmed, "boucles") == 0) {
        printf("🔄 Boucles actives (%d/%d):\n", loop_count, MAX_LOOPS);
        for (int i = 0; i < loop_count; i++) {
            if (loops[i].type == 0) {
                printf("   Boucle while: %s\n", loops[i].condition);
            } else {
                printf("   Boucle for: %s de %d à %d (actuel: %d)\n", 
                       loops[i].variable, loops[i].start_value, 
                       loops[i].end_value, loops[i].current_iteration);
            }
        }
    } else if (strcmp(trimmed, "stats") == 0) {
        printf("📈 Statistiques Wesh:\n");
        printf("   Variables: %d/%d\n", var_count, MAX_VARIABLES);
        printf("   Boucles: %d/%d\n", loop_count, MAX_LOOPS);
        printf("   Blagues disponibles: %d\n", nombre_blagues);
        printf("   Mode debug: %s\n", debug_mode ? "activé" : "désactivé");
    } else {
        printf("❌ Erreur teubé! Commandes: debug on/off, variables, boucles, stats\n");
    }
}

// renoi - Générer des nombres aléatoires
void process_renoi(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return;
    }
    
    int min, max;
    char var_name[MAX_VAR_NAME];
    
    if (sscanf(command, "%d à %d dans %s", &min, &max, var_name) == 3) {
        static int seed_initialized = 0;
        if (!seed_initialized) {
            srand(time(NULL));
            seed_initialized = 1;
        }
        
        int random_num = min + rand() % (max - min + 1);
        set_variable(var_name, random_num, NULL, 1);
        printf("🎲 Nombre aléatoire %d généré dans '%s'\n", random_num, var_name);
    } else if (sscanf(command, "%d à %d", &min, &max) == 2) {
        static int seed_initialized = 0;
        if (!seed_initialized) {
            srand(time(NULL));
            seed_initialized = 1;
        }
        
        int random_num = min + rand() % (max - min + 1);
        printf("🎲 Nombre aléatoire: %d\n", random_num);
    } else {
        printf("❌ Erreur renoi! Utilise: ^ renoi : [min] à [max] ou [min] à [max] dans [variable]\n");
        printf("📝 Exemple: ^ renoi : 1 à 10 dans nombre\n");
    }
}

// fini - Fin de boucle améliorée
void process_fini() {
    if (current_loop >= 0 && loops[current_loop].active) {
        Loop* loop = &loops[current_loop];
        
        if (loop->type == 0) { // while
            loop->loop_counter++;
            if (loop->loop_counter > 1000) { // Protection contre les boucles infinies
                printf("⚠️  Boucle while arrêtée (trop d'itérations)!\n");
                loop->active = 0;
                current_loop = -1;
                return;
            }
            
            if (evaluate_condition(loop->condition)) {
                fseek(current_file, loop->file_position, SEEK_SET);
                if (debug_mode) {
                    printf("🔄 Boucle while continue (itération %d)...\n", loop->loop_counter);
                }
                return;
            }
        } else if (loop->type == 1) { // for
            loop->current_iteration++;
            if (loop->current_iteration <= loop->end_value) {
                set_variable(loop->variable, loop->current_iteration, NULL, 1);
                fseek(current_file, loop->file_position, SEEK_SET);
                if (debug_mode) {
                    printf("🔄 Boucle for continue: %s = %d\n", loop->variable, loop->current_iteration);
                }
                return;
            }
        }
        
        // Fin de la boucle
        loop->active = 0;
        current_loop = -1;
        printf("✅ Boucle terminée mon poto!\n");
    }
}

// Fonction principale pour traiter une ligne
void process_line(char* line) {
    char* trimmed = trim(line);
    
    // Ignorer les lignes vides ou les commentaires
    if (strlen(trimmed) == 0 || trimmed[0] == '#') {
        return;
    }
    
    // Vérifier si c'est une ligne "alors" 
    char* alors_check = strstr(trimmed, "alors");
    if (alors_check != NULL && strstr(alors_check, "^") != NULL) {
        char* command_start = strstr(alors_check, "^");
        process_line(command_start);
        return;
    } else if (strcmp(trimmed, "alors") == 0) {
        process_alors();
        return;
    }
    
    // Vérifier si c'est "fini" pour les boucles
    if (strcmp(trimmed, "fini") == 0) {
        process_fini();
        return;
    }
    
    if (trimmed[0] != '^') {
        return;
    }
    
    char* command = trimmed + 1;
    command = trim(command);
    
    if (strncmp(command, "Wsh -", 5) == 0) {
        process_wsh(trim(command + 5));
    } else if (strncmp(command, "Capté :", 7) == 0) {
        process_capte(trim(command + 7));
    } else if (strncmp(command, "quoicoubeh", 10) == 0) {
        process_quoicoubeh(trim(command + 10));
    } else if (strncmp(command, "poto :", 6) == 0) {
        process_poto(trim(command + 6));
    } else if (strncmp(command, "watt :", 6) == 0) {
        process_watt(trim(command + 6));
    } else if (strncmp(command, "reuf :", 6) == 0) {
        process_reuf(trim(command + 6));
    } else if (strncmp(command, "Cité -", 6) == 0) {
        process_cite(trim(command + 6));
    } else if (strncmp(command, "crampté -", 9) == 0) {
        process_crampte(trim(command + 9));
    } else if (strncmp(command, "bogoss :", 8) == 0) {
        process_bogoss(trim(command + 8));
    } else if (strncmp(command, "gadjo :", 7) == 0) {
        process_gadjo(trim(command + 7));
    } else if (strncmp(command, "pélo :", 6) == 0) {
        process_pelo(trim(command + 6));
    } else if (strncmp(command, "sah :", 5) == 0) {
        process_sah(trim(command + 5));
    } else if (strncmp(command, "wAllah :", 8) == 0) {
        process_wallah(trim(command + 8));
    } else if (strncmp(command, "daronne :", 9) == 0) {
        process_daronne(trim(command + 9));
    } else if (strncmp(command, "zonzon :", 8) == 0) {
        process_zonzon(trim(command + 8));
    } else if (strncmp(command, "turfu :", 7) == 0) {
        process_turfu(trim(command + 7));
    } else if (strncmp(command, "teubé :", 7) == 0) {
        process_teube(trim(command + 7));
    } else if (strncmp(command, "renoi :", 7) == 0) {
        process_renoi(trim(command + 7));
    } else {
        printf("❌ Commande inconnue: '%s'\n", command);
        printf("🔍 Commandes disponibles:\n");
        printf("   📝 Base: Wsh, Capté, watt, poto, reuf, Cité, crampté, quoicoubeh\n");
        printf("   🔄 Boucles: bogoss, gadjo\n");
        printf("   📊 Données: pélo, sah, wAllah, daronne, zonzon\n");
        printf("   🔥 Avancé: turfu, teubé, renoi\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3 || strcmp(argv[1], "wsh") != 0) {
        printf("Usage: %s wsh <fichier.wsh>\n", argv[0]);
        return 1;
    }
    
    current_file = fopen(argv[2], "r");
    if (current_file == NULL) {
        printf("❌ Erreur: impossible d'ouvrir le fichier %s\n", argv[2]);
        return 1;
    }
    
    printf("🔥 Exécution du programme Wesh ULTIME: %s 🔥\n\n", argv[2]);
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), current_file)) {
        line[strcspn(line, "\n")] = 0;
        process_line(line);
        
        // Réinitialiser le contexte conditionnel après une ligne "alors" exécutée
        if (in_condition_block && strstr(line, "alors") != NULL) {
            in_condition_block = 0;
            execute_then_block = 0;
        }
    }
    
    fclose(current_file);
    printf("\n🎯 Programme Wesh ULTIME terminé, à plus dans le bus poto! 🎯\n");
    return 0;
}
