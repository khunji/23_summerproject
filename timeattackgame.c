#define NUM_WORDS 20
#define DISPLAY_TIME 1000 // �ܾ� �� �� �����ִµ� ��� �ð� 1�� (�и��� ������ ǥ��)
#define INPUT_TIME 5000  // �ܾ� �� �� �Է��ϴµ� �־��� �ð� 5�� (�и��� ����)

#include <stdio.h>
#include <stdlib.h> // system �Լ�, "cls" (Windows���� ȭ���� ����� ��ɾ�)
#include <string.h> // strcmp (���ڿ��� ���ϴ� �Լ�), ����ڰ� �Է��� �ܾ�� ���� �ܾ ���ϴµ� ���
#include <windows.h> // Sleep �Լ� (���� �����带 ���� �ð� ���� ����Ű�µ� ���, �� �ܾ �����ִ� �ð��� ������), _kbhit �Լ� (Ű���忡�� �Էµ� ���ڸ� Ȯ���ϴµ� ���Ǹ�, �ش� �ڵ忡���� ����ڰ� �ܾ �Է��ߴ��� ���θ� üũ�Ѵ�.)
#include <time.h> // time_t ���

void showing_word(char* word); // �ܾ �����ش�
void fade_away(); // ȭ�� ������� ��
int compare(const void* a, const void* b); // qsort �Լ��� ����� �� �Լ�

int main()
{
    int point = 0;
    char* animal_quiz[NUM_WORDS] = {
        "human","tiger","dragon","monkey","bird",
        "cormorant","armadillo","pigeon","parrot","dog",
        "cat","killer whale","anteater","sloth","fox",
        "jaguar","puma","capybara","lion","boar"
    }; // ������ �ܾ��

    // �ܾ���� ���� ������ ����
    qsort(animal_quiz, NUM_WORDS, sizeof(char*), compare);

    printf("Press Enter to start the game!!");
    getchar(); // �Է��� �޴´�



    for (int i = 0; i < NUM_WORDS; i++)
    {
        printf("\nCurrent Score: %d\n", point);
        showing_word(animal_quiz[i]); // �Ű����� animal_quiz[i]�� �ܾ �Ű������� ����
        Sleep(DISPLAY_TIME); // Sleep �Լ��� ����Ͽ� display_time�� �ð� 1�ʸ�ŭ �Ͻ������� ��Ű�� ��
        fade_away();

        printf("\n%s", "Enter the word: ");
        time_t timestart = time(NULL); // time(NULL) �Լ��� �ý����� ���� �ð��� �� ������ ��ȯ, time_t�� �ð� ������ �����ϴ� ������ ����, ���ӿ��� �ð� ������ �����ϴµ� ����ϴ� �ڵ�. timestart�� ���� �ð��� ���������ν� �÷��̾ �ܾ �Է��ϱ� ������ �ð��� ���.

        while (difftime(time(NULL), timestart) * 1000 <= INPUT_TIME) // c���� difftime �Լ��� ������ ����� �� ���, difftime(time(NULL), timestart)�� ���� �ð��� timestart ������ ���̸� �� ������ ��ȯ.
        {
            if (_kbhit()) // Ű�� Ű���忡�� ���ȴ��� Ȯ���Ѵ�.
            {
                char wordinput[200];

                fgets(wordinput, sizeof(wordinput), stdin); // stdin���� ����ڰ� Ű����� �Է��� ���ڿ��� wordinput �迭�� �����Ѵ�. sizeof(wordinput)�� wordinput �迭�� ũ�⸦ ��Ÿ����. �Է¹��� �ִ� ���ڿ� ���̸� �����Ѵ�->�����÷ο� ����, stdin ����ؼ� Ű����� �Է��� ���ڿ��� ���α׷����� �޾ƿ´�. fgets �Լ� ��ü�� �Էµ� ���ڵ�� �Բ� ���๮�ڸ� �Է¹��ۿ��� �����´�.

                wordinput[strcspn(wordinput, "\n")] = '\0'; // ���� ����ڰ� �Է��� ���ڿ��� wordinput�� ����Ǿ� �ִ�. strcspn�� wordinput ���ڿ����� ���๮�� "\n"�� ó������ ��Ÿ���� ��ġ�� ã�Ƽ� ��ȯ�Ѵ�. �׸��� �̰��� �η� �ٲ��ش�.

                if (strcmp(wordinput, animal_quiz[i]) == 0) // strcmp�� ���ڿ��� ���ϴ� �Լ� string.h���� �����´�. strcmp�� ()�ȿ� ���Ϸ��� ���ڿ��� ������ 0�̶�� �Ѵ�.
                {
                    point += 1;
                }
                else
                {
                    point -= 1;
                }
                break;
            }
        }

        showing_word("Next word will appear!!!");
        Sleep(DISPLAY_TIME);
        fade_away();
    }

    printf("\n\nGame Over! Your Record is %d\n", point);

    return 0;
}

void showing_word(char* word)
{
    printf("\n****************************************\n");
    printf("            wordinput:%s                \n", word);
    printf("\n****************************************\n");
}

void fade_away()
{
    system("cls"); // window �ü������ ����ϴ� ��. ���� ȭ�鿡 ��µ� ������ ��� �����ִ� ��. cls -> clear screen
}

int compare(const void* a, const void* b)
{
    // ���� ���� ���Ͽ� ����
    return strlen(*(char**)a) - strlen(*(char**)b);
}
