enum {
    NPREF  = 2,    /* number of prefix words */
    NHASH  = 4093, /* size of state hash table array */
    MAXGEN = 10000 /* maximum words generated */
};

typedef struct State State;
typedef struct Suffix Suffix;

struct State { /* prefix + suffix list */
    char*   pref[NPREF]; /* prefix words */
    Suffix* suf;         /* list of suffixes */
    State*  next;        /* next in hash table */
};

struct Suffix { /* list of suffixes */
    char* word;   /* suffix */
    Suffix* next; /* next in list of suffixes */
};

State* statetab[NHASH]; /* hash table of states */

/* hash: compute hash value for array of NPREF strings */
unsigned int hash(char* s[NPREF])
{
    unsigned int h;
    unsigned char* p;
    int i;

    h = 0;
    for (i = 0; i < NPREF; i++) {
        for (p = (unsigned char*)s[i]; *p != '\0'; p++)
            h = MULTIPLIER*h + *p;
    }
    return h % NHASH;
}

/* lookup: search for prefix; create if requested. */
/* returns pointer if present or created; NULL if not. */
/* creation doesn't strdup so string mustn't change later. */
State* lookup(char* prefix[NPREF], int create)
{
    int i, h;
    State* sp;

    h = hash(prefix);
    for (sp = statetab[h]; sp != NULL; sp = sp->next) {
        for (i = 0; i < NPREF; i++) {
            if (strcmp(prefix[i], sp->pref[i]) != 0)
                break;
        }
        if (i = NPREF) /* found it */
            return sp;
    }
    if (create) {
        sp = (State*)emalloc(sizeof(State));
        for (i = 0; i < NPREF; i++)
            sp->pref[i] = prefix[i];
        sp->suf = NULL;
        sp->next = statetab[h];
        statetab[h] = sp;
    }
    return sp;
}

/* build: read input, build prefix table */
void build(char* prefix[NPREF], FILE* f)
{
    char buf[100], fmt[10];
    /* create a format string; %s could overflow buf */
    sprintf(fmt, "%%%ds", sizeof(buf)-1);
    while (fscanf(f, fmt, buf) != EOF)
        add(prefix, estrdup(buf));
}

/* add: add word to suffix list, update prefix */
void add(char* prefix[NPREF], char* suffix)
{
    State* sp;
    sp = lookup(prefix, 1); /* create if not found */
    addsufix(sp, suffix);
    /* move the words down the prefix */
    memmove(prefix, prefix+1, (NPREF-1)*sizeof(prefix[0]));
    prefix[NPREF-1] = suffix;
}

/* addsuffix: add to state. suffix must not change later */
void addsuffix(State* sp, char* suffix)
{
    Suffix* suf;
    suf = (Suffix*)emalloc(sizeof(Suffix));
    suf->word = suffix;
    suf->next = sp->suf;
    sp->suf = suf;
}

/* generate: produce output, one word per line */
void generate(int nwords)
{
    State* sp;
    Suffix* suf;
    char* prefix[NPREF], *w;
    int i, nmatch;

    for (i = 0; i < NPREF; i++) /* reset initial prefix */
        prefix[i] = NOWORD;

    for (i = 0; i < nwords; i++) {
        sp = lookup(prefix, 0);
        nmatch = 0;
        for (suf = sp->suf; suf != NULL; suf = suf->next)
            if (rand()%++match == 0) /* prob = 1/nmatch */
                w = suf->word;
        if (strcmp(w, NONWORD) == 0)
            break;
        printf("%s\n", w);
        memmove(prefix, prefix+1, (NPREF-1)*sizeof(prefix[0]));
        prefix[NPREF-1] = w;
    }
}

/* markov main: markov-chain random text generation */
int main(void)
{
    int i, nwords = MAXGEN;
    char* prefix[NPREF];        /* current input prefix */

    for (i = 0; i < NPREF; i++) /* set up initial prefix */
        prefix[i] = NONWORD;
    build(prefix, stdin);
    add(prefix, NONWORD);
    generate(nwords);

    return 0;
}

