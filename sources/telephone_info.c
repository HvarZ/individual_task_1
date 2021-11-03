#include "telephone_info.h"

#define MAX_NUMBER_TELEPHONES 100000
#define MAX_LENGTH_NAME 20
#define MAX_NETWORK_CODE 9999
#define MAX_NUMBER 9999999
#define MIN_NUMBER 1000000

void CreateBase(base_t *base) {
    if (base == NULL) {
        return;
    }
    base->capacity_ = 1;
    base->telephoneCount_ = 0;
    base->telephones = (telephone_t*)malloc(sizeof(telephone_t));
}

void Add(base_t *base, unsigned long networkCode,
         unsigned long number, const char *nameOwner) {
    if (base->telephoneCount_ >= MAX_NUMBER_TELEPHONES) {
        return;
    }
    if (base->capacity_ == base->telephoneCount_) {
        base->capacity_ *= 2;
        base->telephones = (telephone_t*)realloc(base->telephones, base->capacity_ * sizeof(telephone_t));
    }
    base->telephones[base->telephoneCount_].networkCode_ = networkCode;
    base->telephones[base->telephoneCount_].number_ = number;

    if (nameOwner != NULL) {
        base->telephones[base->telephoneCount_].nameOwner_ = malloc((strlen(nameOwner) + 1));
        strcpy(base->telephones[base->telephoneCount_].nameOwner_, nameOwner);
    } else {
        base->telephones[base->telephoneCount_].nameOwner_ = malloc(sizeof(char));
        strcpy(base->telephones[base->telephoneCount_].nameOwner_, (const char*)(""));
    }
    base->telephoneCount_++;
}

void FillBase(base_t *base) {
    if (base == NULL) {
        return;
    }
    unsigned long networkCode;
    while (scanf("%lu", &networkCode) != EOF) {
        unsigned long number;
        scanf("%lu", &number);

        char* nameOwner = malloc(MAX_LENGTH_NAME);
        scanf("%s", nameOwner);
        if (!IsValidNumber(networkCode, number)) {
            continue;
        }
        Add(base, networkCode, number, nameOwner);
    }
}

void DeleteBase(base_t *base) {
    if (base == NULL) {
        return;
    }
    for (unsigned long i = 0; i < base->telephoneCount_; ++i) {
        if (base->telephones[i].nameOwner_ != NULL) {
            free(base->telephones[i].nameOwner_);
        }
    }
    free(base->telephones);
}

bool IsValidNumber(unsigned long networkCode, unsigned long number) {
    return networkCode <= MAX_NETWORK_CODE && (number >= MIN_NUMBER && number <= MAX_NUMBER);
}

void Print(base_t* base) {
    if (base == NULL || base->telephoneCount_ == 0) {
        printf("Base is empty");
        return;
    }
    Sort(base);
    for (unsigned long i = 0; i < base->telephoneCount_; ++i) {
        if (base->telephones[i].nameOwner_ != NULL) {
            setbuf(stdout, 0);
            printf("+%lu%lu - %s\n", base->telephones[i].networkCode_,
                   base->telephones[i].number_, base->telephones[i].nameOwner_);
        }
    }
}

void Sort(base_t *base) {
    if (base == NULL) {
        return;
    }
    telephone_t tmp;
    for (unsigned long i = 1; i < base->telephoneCount_; ++i) {
        for (unsigned long j = 0; j < base->telephoneCount_ - 1; ++j) {
            if (base->telephones[j].networkCode_ > base->telephones[j + 1].networkCode_) {
                tmp = base->telephones[j];
                base->telephones[j] = base->telephones[j + 1];
                base->telephones[j + 1] = tmp;
            }
        }
    }
}


