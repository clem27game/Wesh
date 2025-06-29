
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
    "Qu'est-ce qui est invisible et qui sent la carotte ? Un pet de lapin invisible !",
    "Comment appelle-t-on un facteur qui ne distribue que les mauvaises nouvelles ? Un facteur de risque !",
    "Que dit un balai qui en a marre ? J'en ai ras le bol !",
    "Pourquoi les vikings n'allaient jamais au restaurant ? Parce qu'ils préféraient piller !",
    "Qu'est-ce qui a 4 roues et 1 moteur mais qui n'avance pas ? Une voiture en panne !",
    "Comment fait un Schtroumpf pour communiquer ? Il Schtroumpfe !",
    "Que dit un cannibale après avoir mangé sa belle-mère ? C'était dur à avaler !",
    "Pourquoi les lapins sont toujours pressés ? Parce qu'ils courent après le temps !",
    "Qu'est-ce qui est petit, rouge et qui monte et descend ? Une tomate dans un ascenseur !",
    "Comment appelle-t-on un arbre qui fait du karaté ? Un bambou !",
    "Que dit un crocodile qui surveille la pharmacie ? Lacoste garde !",
    "Pourquoi les toilettes sont-elles carrées ? Parce que les rondes, c'est des trous !",
    "Qu'est-ce qui a des feuilles mais n'est pas un arbre ? Un livre !",
    "Comment fait-on pour énerver un archéologue ? On lui donne un os à ronger !",
    "Que dit un serpent quand on lui marche dessus ? Aïe-Python !",
    "Pourquoi les abeilles ont-elles les cheveux collants ? Parce qu'elles utilisent des honey-combs !",
    "Qu'est-ce qui a des dents mais ne mord jamais ? Une fermeture éclair !",
    "Comment appelle-t-on un taureau qui fait de la peinture ? Un taureau-pinceau !",
    "Que dit un escargot quand il fait de l'auto-stop ? Es-cargo !",
    "Pourquoi les fantômes ne mentent jamais ? Parce qu'on peut voir à travers eux !",
    "Qu'est-ce qui a un lit mais ne dort jamais ? Une rivière !"
};
const int nombre_blagues = 59;

// Variables pour la gestion des conditions
int condition_result = 0;
int in_condition_block = 0;
int execute_then_block = 0;

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
    } else if (strcmp(color, "rose") == 0 || strcmp(color, "pink") == 0) {
        printf("\033[35m%s\033[0m\n", message);
    } else if (strcmp(color, "cyan") == 0) {
        printf("\033[36m%s\033[0m\n", message);
    } else if (strcmp(color, "blanc") == 0) {
        printf("\033[37m%s\033[0m\n", message);
    } else if (strcmp(color, "violet") == 0) {
        printf("\033[35m%s\033[0m\n", message);
    } else if (strcmp(color, "orange") == 0) {
        printf("\033[33m%s\033[0m\n", message);
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
    char* trimmed_expr = trim(expr);
    
    // Trouve l'opérateur
    char* op_pos = NULL;
    char op = 0;
    
    // Chercher les opérateurs dans l'ordre de priorité
    if ((op_pos = strstr(trimmed_expr, " + ")) != NULL) {
        op = '+';
        op_pos += 1; // Pointer sur le '+'
    } else if ((op_pos = strstr(trimmed_expr, " - ")) != NULL) {
        op = '-';
        op_pos += 1; // Pointer sur le '-'
    } else if ((op_pos = strstr(trimmed_expr, " * ")) != NULL) {
        op = '*';
        op_pos += 1; // Pointer sur le '*'
    } else if ((op_pos = strstr(trimmed_expr, " / ")) != NULL) {
        op = '/';
        op_pos += 1; // Pointer sur le '/'
    }
    
    if (op_pos == NULL) {
        // Vérifier si c'est une variable
        Variable* var = find_variable(trimmed_expr);
        if (var && var->is_number) {
            return var->value;
        }
        return atoi(trimmed_expr);
    }
    
    *op_pos = '\0';
    char* left_str = trim(expr);
    char* right_str = trim(op_pos + 1);
    
    int left, right;
    
    // Évaluer la partie gauche
    Variable* var_left = find_variable(left_str);
    if (var_left && var_left->is_number) {
        left = var_left->value;
    } else {
        left = atoi(left_str);
    }
    
    // Évaluer la partie droite
    Variable* var_right = find_variable(right_str);
    if (var_right && var_right->is_number) {
        right = var_right->value;
    } else {
        right = atoi(right_str);
    }
    
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return right != 0 ? left / right : 0;
        default: return 0;
    }
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
        return 0; // Condition invalide
    }
    
    *op_pos = '\0';
    char* left_str = trim(cond);
    char* right_str = trim(op_pos + strlen(op));
    
    int left, right;
    
    // Évaluer la partie gauche
    Variable* var_left = find_variable(left_str);
    if (var_left && var_left->is_number) {
        left = var_left->value;
    } else {
        left = atoi(left_str);
    }
    
    // Évaluer la partie droite
    Variable* var_right = find_variable(right_str);
    if (var_right && var_right->is_number) {
        right = var_right->value;
    } else {
        right = atoi(right_str);
    }
    
    // Appliquer l'opérateur
    if (strcmp(op, ">") == 0) return left > right;
    if (strcmp(op, "<") == 0) return left < right;
    if (strcmp(op, ">=") == 0) return left >= right;
    if (strcmp(op, "<=") == 0) return left <= right;
    if (strcmp(op, "==") == 0) return left == right;
    if (strcmp(op, "!=") == 0) return left != right;
    
    return 0;
}

// Fonction pour traiter les commandes Wsh
void process_wsh(const char* message) {
    if (in_condition_block && !execute_then_block) {
        return; // Ne pas exécuter si on est dans un bloc conditionnel false
    }
    
    // Enlever les guillemets si présents
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
        return; // Ne pas exécuter si on est dans un bloc conditionnel false
    }
    
    int result = evaluate_math(expression);
    printf("%d\n", result);
}

// Fonction pour traiter quoicoubeh (blagues)
void process_quoicoubeh(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return; // Ne pas exécuter si on est dans un bloc conditionnel false
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
        printf("🤣 Voici une blague pour toi:\n");
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
        // Démarrer une nouvelle condition
        in_condition_block = 1;
        condition_result = evaluate_condition(trimmed + 3);
        execute_then_block = condition_result;
    }
}

// Fonction pour traiter "alors"
void process_alors() {
    // Cette fonction sera appelée quand on rencontre "alors"
    // L'état est déjà géré par process_poto
}

// Fonction pour traiter watt (définition de variables)
void process_watt(const char* definition) {
    if (in_condition_block && !execute_then_block) {
        return; // Ne pas exécuter si on est dans un bloc conditionnel false
    }
    
    char var_name[MAX_VAR_NAME];
    char value_str[MAX_LINE_LENGTH];
    
    // Parser "variable = valeur"
    if (sscanf(definition, "%s = %[^\n]", var_name, value_str) == 2) {
        char* trimmed_value = trim(value_str);
        
        // Vérifier si c'est un nombre ou du texte
        if (isdigit(trimmed_value[0]) || (trimmed_value[0] == '-' && isdigit(trimmed_value[1]))) {
            int value = atoi(trimmed_value);
            set_variable(var_name, value, NULL, 1);
            printf("✅ Variable '%s' définie avec la valeur %d\n", var_name, value);
        } else {
            set_variable(var_name, 0, trimmed_value, 0);
            printf("✅ Variable '%s' définie avec la valeur %s\n", var_name, trimmed_value);
        }
    }
}

// Fonction pour traiter reuf (couleurs)
void process_reuf(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return; // Ne pas exécuter si on est dans un bloc conditionnel false
    }
    
    char color[50];
    char message[MAX_LINE_LENGTH];
    char* trimmed_command = trim((char*)command);
    
    // Parser "couleur X - "message"" (avec guillemets)
    if (sscanf(trimmed_command, "couleur %s - \"%[^\"]\"", color, message) == 2) {
        print_color(color, message);
    } 
    // Parser "couleur X - message" (sans guillemets)
    else if (sscanf(trimmed_command, "couleur %s - %[^\n]", color, message) == 2) {
        // Enlever les éventuels guillemets au début et à la fin
        char* clean_msg = trim(message);
        if (clean_msg[0] == '"' && clean_msg[strlen(clean_msg)-1] == '"') {
            clean_msg[strlen(clean_msg)-1] = '\0';
            clean_msg++;
        }
        print_color(color, clean_msg);
    } 
    else {
        printf("❌ Erreur de syntaxe reuf! Utilise: ^ reuf : couleur [couleur] - \"[message]\"\n");
        printf("🎨 Couleurs disponibles: rouge, vert, bleu, jaune, rose, cyan, blanc, violet, orange\n");
    }
}

// Fonction pour traiter Cité (délais)
void process_cite(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return; // Ne pas exécuter si on est dans un bloc conditionnel false
    }
    
    int ms;
    if (sscanf(command, "%d ms", &ms) == 1) {
        printf("⏱️  Délai de %d ms...\n", ms);
        usleep(ms * 1000); // convertir ms en microseconds
    } else {
        printf("❌ Erreur: format incorrect pour Cité. Utilise: ^ Cité - [nombre] ms\n");
    }
}

// Fonction pour traiter crampté (modification de message)
void process_crampte(const char* command) {
    if (in_condition_block && !execute_then_block) {
        return; // Ne pas exécuter si on est dans un bloc conditionnel false
    }
    
    char initial[MAX_LINE_LENGTH];
    char final[MAX_LINE_LENGTH];
    int ms;
    
    // Trimmer la commande
    char trimmed_command[MAX_LINE_LENGTH];
    strcpy(trimmed_command, command);
    char* cmd = trim(trimmed_command);
    
    if (sscanf(cmd, "\"%[^\"]\", %d ms , \"%[^\"]\"", initial, &ms, final) == 3) {
        printf("🔄 %s", initial);
        fflush(stdout);
        usleep(ms * 1000);
        // Effacer la ligne précédente et afficher le nouveau message
        printf("\r\033[2K✅ %s\n", final);
        fflush(stdout);
    } else {
        printf("❌ Erreur de syntaxe crampté! Utilise: ^ crampté - \"message initial\", [délai] ms , \"message final\"\n");
        printf("📝 Exemple: ^ crampté - \"Chargement...\", 1000 ms , \"Terminé!\"\n");
    }
}

// Fonction principale pour traiter une ligne
void process_line(char* line) {
    char* trimmed = trim(line);
    
    // Ignorer les lignes vides ou les commentaires
    if (strlen(trimmed) == 0 || trimmed[0] == '#') {
        return;
    }
    
    // Vérifier si c'est une ligne "alors" (peut être indentée)
    char* alors_check = strstr(trimmed, "alors");
    if (alors_check != NULL && strstr(alors_check, "^") != NULL) {
        // C'est une ligne "alors" avec une commande
        char* command_start = strstr(alors_check, "^");
        process_line(command_start); // Traiter la commande après "alors"
        return;
    } else if (strcmp(trimmed, "alors") == 0) {
        process_alors();
        return;
    }
    
    if (trimmed[0] != '^') {
        return; // Ignorer les lignes qui ne commencent pas par ^
    }
    
    char* command = trimmed + 1; // Enlever le ^
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
    } else {
        printf("❌ Commande inconnue: %s\n", command);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3 || strcmp(argv[1], "wsh") != 0) {
        printf("Usage: %s wsh <fichier.wsh>\n", argv[0]);
        return 1;
    }
    
    FILE* file = fopen(argv[2], "r");
    if (file == NULL) {
        printf("❌ Erreur: impossible d'ouvrir le fichier %s\n", argv[2]);
        return 1;
    }
    
    printf("🔥 Exécution du programme Wesh: %s 🔥\n\n", argv[2]);
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // Enlever le retour à la ligne
        line[strcspn(line, "\n")] = 0;
        process_line(line);
        
        // Réinitialiser le contexte conditionnel après une ligne "alors" exécutée
        if (in_condition_block && strstr(line, "alors") != NULL) {
            in_condition_block = 0;
            execute_then_block = 0;
        }
    }
    
    fclose(file);
    printf("\n 🎯 Programme Wesh terminé, à plus dans le bus poto! 🎯\n");
    return 0;
}
