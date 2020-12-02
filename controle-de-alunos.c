/* Lucas Purcino Simoes
 * Gerenciamento de uma escola.
 * Usar: estrutura, vetor, função.
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

#define MAX_ALUNOS 99 /*0-99 = 100 alunos*/
#define MAX_DISCIPLINAS 6 /*0-6 = 7 disciplinas*/

#define DEBUG 0

//estrutura disciplinas
typedef struct Disciplinas_struct
{
    char nome_disciplina[15];
    float nota_p1;
    float nota_p2;
} Disciplina;

//estrutura alunos
typedef struct Alunos_struct
{
    char nome[60];
    char RA[8];
    Disciplina disciplina[MAX_DISCIPLINAS];

} Alunos;

//inclui alunos OK
/*index - para saber a index a adicionar o proximo aluno*/
void incluir_aluno(Alunos aluno[], int *index)
{
    system("cls");
    printf("== INCLUIR ALUNO(S) == \n");

    printf("Quantos alunos a incluir? ");
    int qnt = 0;
    scanf("%d", &qnt);

    int aux = *index; //usar aux como index

    for(int i = 0; i <= qnt-1; i++)
    {
        printf("\nAluno %d\n", i+1);
        printf("\n\tNome: ");
        fflush(stdin);
        scanf("%s", &aluno[aux].nome);
        printf("\n\tRA: ");
        fflush(stdin);
        scanf("%s", &aluno[aux].RA);

        //cadastra disciplinas
        printf("\nNúmero de disciplinas: ");
        int qnt_disciplinas = 0;
        scanf("%d", &qnt_disciplinas);

        for(int j = 0; j <= qnt_disciplinas-1; j++)
        {
            printf("\n\tNome da disciplina: ");
            fflush(stdin);
            scanf("%s", &aluno[aux].disciplina[j].nome_disciplina);
            printf("\n\tNota P1: ");
            fflush(stdin);
            scanf("%f", &aluno[aux].disciplina[j].nota_p1);
            printf("\n\tNota P2: ");
            fflush(stdin);
            scanf("%f", &aluno[aux].disciplina[j].nota_p2);

            *index += 1; //posição do proximo index para adicionar proximo aluno
        }
        system("cls");
    }
}

//remove aluno por RA
void remove_aluno(Alunos aluno[], int index) //index para economizar loop, só passa o loop na quantidades de alunos armazenados
{
    system("cls");
    printf("\n== REMOVER ALUNO ==\n");

    char RA[8];
    printf("RA do aluno: ");
    fflush(stdin);
    scanf("%s", &RA);

    //busca o alnuo
    for(int i = 0; i <= index; i++) //usando index para não precisar do MAX_ALUNOS, economizando loop
    {
        if( strcmp(aluno[i].RA, RA) == 0 ) //se o RA inserido é igual
        {
            char removido[60]; //guardar nome para o alerta da remoção
            strcpy( removido, aluno[i].nome);

            strcpy( aluno[i].nome, "\0" );
            strcpy( aluno[i].RA, "\0" );

            //loop nas disciplinas - limpa dados das disciplinas
            for(int j = 0; j <= MAX_DISCIPLINAS; j++)
            {
                if( strcmp(aluno[i].disciplina[0].nome_disciplina, "") == 0 ) //index 0 pois se não tiver no primeiro index não tem nos outros
                    break;
                if( strcmp(aluno[i].disciplina[j].nome_disciplina, "") != 0 ) //!= 0 quer dizer que a string não e vazia (não tem disciplina)
                {
                    strcpy( aluno[i].disciplina[j].nome_disciplina, "" );
                    aluno[i].disciplina[j].nota_p1 = 0.00f;
                    aluno[i].disciplina[j].nota_p2 = 0.00f;

                    if(strcmp(aluno[i].disciplina[j+1].nome_disciplina, "") == 0) //economizar loop, se no proximo index não tiver mais dados, nos outros não tem.
                        break;
                }
            }

            printf("\n\t Os registros do aluno %s foram removidos.", removido);
            break; //se já encontrou o aluno, descontinua o loop
        }

        if( strcmp(aluno[i].RA, "") == 0)
        {
            printf("\n[!] Não há registros no sistema. Aluno não encontrado.\n");
            break; //se não tem RA não há registros, então para o loop
        }
    }
    printf("\n\n"); //quebra linha
}

//altera informações de aluno
void alterar_informacoes(Alunos aluno[], int index)
{
    system("cls");
    printf("\n== ALTERAR INFORMAÇÕES ==\n");

    char RA[8];
    printf("RA do aluno: ");
    fflush(stdin);
    scanf("%s", &RA);

    //busca o alnuo
    for(int i = 0; i <= index; i++) //usando index para não precisar do MAX_ALUNOS, economizando loop
    {
        if( strcmp(aluno[i].RA, RA) == 0 ) //se o RA inserido é igual
        {
            printf("\nAlterar informações do aluno: %s.\n (Precione [ENTER] para não alterar.)\n", aluno[i].nome);

            char novo_nome[60];
            printf("\nNovo nome(%s): ", aluno[i].nome);
            fflush(stdin);
            gets(novo_nome);

            if(  strcmp(novo_nome, "") != 0 ) //não consegui com strcmp(novo_nome, "\n") \n por conto do <ENTER>
                strcpy( aluno[i].nome, novo_nome );

            //loop nas disciplinas
            for(int j = 0; j <= MAX_DISCIPLINAS; j++)
            {
                if( strcmp(aluno[i].disciplina[0].nome_disciplina, "") == 0 ) //index 0 pois se não tiver no primeiro index não tem nos outros
                {
                    printf("[!] Não há disciplinas cadastradas.\n");
                    break;
                }
                if( strcmp(aluno[i].disciplina[j].nome_disciplina, "") != 0 ) //!= 0 quer dizer que a string não e vazia (não tem disciplina)
                {
                    char novo_nome_disc[15];
                    printf("Nova disciplina(%s): ", aluno[i].disciplina[j].nome_disciplina);
                    fflush(stdin);
                    gets(novo_nome_disc);

                    if( strcmp(novo_nome_disc, "") != 0 ) //se o usuario inserir alguma coisa o valor é alterado
                        strcpy( aluno[i].disciplina[j].nome_disciplina, novo_nome_disc );

                    //P1
                    char nova_nota[15]; //pega nota como string para poder comparar com vazio ""
                    printf("\tNova nota P1(%.2f): ", aluno[i].disciplina[j].nota_p1);
                    fflush(stdin);
                    gets(nova_nota);

                    if( strcmp( nova_nota, "" ) != 0)
                        aluno[i].disciplina[j].nota_p1 = atof(nova_nota); //string to double

                    //P2
                    printf("\tNova nota P2(%.2f): ", aluno[i].disciplina[j].nota_p2);
                    fflush(stdin);
                    gets(nova_nota);

                    if( strcmp( nova_nota, "" ) != 0)
                        aluno[i].disciplina[j].nota_p2 = atof(nova_nota); //string to double


                    if(strcmp(aluno[i].disciplina[j+1].nome_disciplina, "") == 0) //economizar loop, se no proximo index não tiver mais dados, nos outros não tem.
                        break;
                }
            }
            printf("\n\t Dados salvos no sistema.\n");

            break; //se já encontrou o aluno, descontinua o loop
        }

        if( strcmp(aluno[i].RA, "") == 0)
        {
            printf("\n[!] Não há registros no sistema. Aluno não encontrado.\n");
            break; //se não tem RA não há registros, então para o loop
        }
    }
    printf("\n\n"); //quebra linha
}

//busca de aluno por RA
void busca_aluno(Alunos aluno[], int index)
{
    system("cls");
    printf("\n== BUSCAR ALUNO ==\n");

    char RA[8];
    printf("RA do aluno: ");
    fflush(stdin);
    scanf("%s", &RA);

    //busca o alnuo
    for(int i = 0; i < index; i++) //usando index para não precisar do MAX_ALUNOS, economizando loop
    {
        if( strcmp(aluno[i].RA, RA) == 0 ) //se o RA inserido é igual
        {
            printf("\nAluno encontrado:\n");
            printf("\tNome: %s\n", aluno[i].nome);
            printf("\tRA: %s\n", aluno[i].RA);

            //loop nas disciplinas
            for(int j = 0; j <= MAX_DISCIPLINAS; j++)
            {
                if( strcmp(aluno[i].disciplina[0].nome_disciplina, "") == 0 ) //index 0 pois se não tiver no primeiro index não tem nos outros
                {
                    printf("[!] Não há disciplinas cadastradas.\n");
                    break;
                }
                if( strcmp(aluno[i].disciplina[j].nome_disciplina, "") != 0 ) //!= 0 quer dizer que a string não e vazia (não tem disciplina)
                {
                    printf("Disciplina: %s\n", aluno[i].disciplina[j].nome_disciplina);
                    printf("\tNota P1: %.2f\n", aluno[i].disciplina[j].nota_p1);
                    printf("\tNota P2: %.2f\n", aluno[i].disciplina[j].nota_p2);

                    if(strcmp(aluno[i].disciplina[j+1].nome_disciplina, "") == 0) //economizar loop, se no proximo index não tiver mais dados, nos outros não tem.
                        break;
                }
            }

            break; //se já encontrou o aluno, descontinua o loop
        }

        if( strcmp(aluno[i].RA, "") == 0)
        {
            printf("\n[!] Não há registros no sistema. Aluno não encontrado.\n");
            break; //se não tem RA não há registros, então para o loop
        }
    }
    printf("\n\n"); //quebra linha
}

//listagem de todos os alunos e *todas as disciplinas e media aritimetira*
void lista_de_alunos_medias(Alunos aluno[], int index)
{
    system("cls");
    printf("\n== LISTA DE ALUNO + MÉDIA ARITMÉTICA ==\n");

    if( strcmp(aluno[0].nome, "") == 0 ) // se nome for vazio não há registros
    {
        printf("\n\t[Sem registros] - Lista indisponível.\n");
        return;
    }

    // loop em todos os alunos
    for(int i = 0; i < index; i++) //usando index para não precisar do MAX_ALUNOS, economizando loop
    {
        printf("\nRegistro %d", i+1); //index + 1 para não ter 'Registro 0'

        printf("\n\tNome: %s", aluno[i].nome);
        printf("\n\tRA: %s", aluno[i].RA);

        for(int j = 0; j <= MAX_DISCIPLINAS; j++)
        {
            if( strcmp(aluno[i].disciplina[0].nome_disciplina, "") == 0 ) //index 0 pois se não tiver no primeiro index não tem nos outros
            {
                printf("\n\t[Não há disciplinas cadastradas]\n");
                break;
            }
            printf("\n\t-Disciplina: %s", aluno[i].disciplina[j].nome_disciplina);
            float media = ( aluno[i].disciplina[j].nota_p1 + aluno[i].disciplina[j].nota_p2 ) / 2;

            printf("\n\t    Média: %.2f\n", media);

            if(strcmp(aluno[i].disciplina[j+1].nome_disciplina, "") == 0) //economizar loop, se no proximo index não tiver mais dados, nos outros não tem.
                break;
        }
        printf("\n");
    }
    printf("\n\n");
}

//listagem de todos os alunos de uma disciplina
void lista_de_alunos_disciplina(Alunos aluno[], int index)
{
    system("cls");
    printf("\n== LISTA DE ALUNUOS POR DISCIPLINA ==\n");

    if( strcmp(aluno[0].nome, "") == 0 ) // se nome for vazio não há registros
    {
        printf("\n\t[Sem registros] - Lista indisponível.\n");
        return;
    }

    char disciplina[8];
    printf("Buscar alunos pela disciplina: ");
    fflush(stdin);
    gets(disciplina);

    printf("\n> Alunos da disciplina: %s", disciplina);

    for(int i = 0; i < index; i++)
    {
        for(int j = 0; j <= MAX_DISCIPLINAS; j++)
        {
            if ( strcmp(aluno[i].disciplina[j].nome_disciplina, disciplina) == 0)
            {
                printf("\n\tAluno: %s\n", aluno[i].nome);
                break;
            }
        }
    }
}

//sair do programa
void sair()
{
    printf("\n\n == VOCÊ SAIU DO PROGRAMA == \n\n");
    exit(1);
}

//menu de escolha
int menu()
{
    setlocale(LC_ALL, "Portuguese");

    printf("========================================\n");
    printf("===== Sistema Cadastro de Alunos =======\n");
    printf("========================================\n");
    printf("1) Cadastrar alunos\n");
    printf("2) Remover aluno\n");
    printf("3) Alterar registro de aluno\n");
    printf("4) Buscar aluno\n");
    printf("5) Listar alunos e médias\n");
    printf("6) Listar alunuos de uma disciplina\n");
    printf("7) Sair do programa\n");
    printf("==> ");

    int escolha = 0;
    fflush(stdin);
    scanf("%d", &escolha);

    if(escolha == 7)
        sair();

    return escolha;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    //estrutura de alunos
    Alunos alunos[MAX_ALUNOS] = {};

    int index = 0;

    #if DEBUG
    strcpy( alunos[0].nome, "lucas");
    strcpy( alunos[0].RA, "123");
    strcpy( alunos[0].disciplina[0].nome_disciplina, "eng soft");
    alunos[0].disciplina[0].nota_p1 = 2.0;
    alunos[0].disciplina[0].nota_p2 = 8.0f;

    strcpy( alunos[1].nome, "pedro");
    strcpy( alunos[1].RA, "321");
    strcpy( alunos[1].disciplina[0].nome_disciplina , "eng soft");
    alunos[1].disciplina[0].nota_p1 = 2.0f;
    alunos[1].disciplina[0].nota_p2 = 9.0f;
    strcpy( alunos[1].disciplina[1].nome_disciplina, "eco");
    alunos[1].disciplina[1].nota_p1 = 7.0f;
    alunos[1].disciplina[1].nota_p2 = 5.0f;

    strcpy( alunos[2].nome, "nicolas");
    strcpy( alunos[2].RA, "333");
    strcpy( alunos[2].disciplina[0].nome_disciplina, "adm");
    alunos[2].disciplina[0].nota_p1 = 6.4;
    alunos[2].disciplina[0].nota_p2 = 2.6f;

    strcpy( alunos[3].nome, "jaam");
    strcpy( alunos[3].RA, "444");

    index = 4;
    #endif // DEBUG

    //loop da aplicacao
    int opt = 0;
    do{
        opt = menu();

        switch(opt)
        {
        case 1: //cadastro de alunos
            incluir_aluno(alunos, &index); //OK
            break;
        case 2: //remover aluno
            remove_aluno(alunos, index); //OK
            break;
        case 3: //alterar dados do aluno
            alterar_informacoes(alunos, index); //OK
            break;
        case 4: //buscar dados do aluno
            busca_aluno(alunos, index); //OK
            break;
        case 5: //listar alunos e média
            lista_de_alunos_medias(alunos, index); //OK
            break;
        case 6: //listar alunos por disciplina
            lista_de_alunos_disciplina(alunos, index); //OK
            break;
        case 7: //sair do programa
            sair(); //OK
            break;

        default:
            system("cls");
            printf("[!] Opção inválida.\n\n");
            break;
        }
    }while(opt != 7); //opt 7 == SAIR

    return 0;
}
