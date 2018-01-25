#ifndef KVADRAT_H
#define KVADRAT_H

#include "csapda.h"

typedef struct {
    int id;
    char kvadratkod;
    int size;
    CsapdaNode *csapdaList;
}Kvadrat;

typedef struct KvadratNode {
    Kvadrat kvadrat;
    struct KvadratNode *next;
}KvadratNode;

/*! \fn const char *Test::member(char c,int n)
 * \brief createEmptyKvadrat
 *  Creates an empty kvadrat, and return the pointer of it
 * \param void
 * \return Kvadrat*
 *
 */
Kvadrat *createEmptyKvadrat(void);

/** \brief
 *  Creates an empty kvadrat node, and return the pointer of it
 * \param kvadrat Kvadrat*
 * \return KvadratNode*
 *
 */
KvadratNode *createKvadratNode(Kvadrat *kvadrat);

/** \brief
 *
 * \param list KvadratNode*
 * \return void
 *
 */
void destroyKvadratList(KvadratNode *list);

/** \brief
 *
 * \param list KvadratNode*
 * \param kvadrat Kvadrat*
 * \return KvadratNode*
 *
 */
KvadratNode *insertKvadrat(KvadratNode *list, Kvadrat *kvadrat);
/** \brief
 *
 * \param list KvadratNode*
 * \return int
 *
 */
int getKvadratListSize(KvadratNode *list);

/** \brief
 *
 * \param list KvadratNode*
 * \param fp FILE*
 * \return KvadratNode*
 *
 */
KvadratNode *readKvadratok(KvadratNode *list, FILE *fp, MODES mode);

/** \brief
 *
 * \param kvadrat Kvadrat*
 * \return void
 *
 */
void printKvadrat(Kvadrat *kvadrat, MODES mode);

/** \brief
 *
 * \param list KvadratNode*
 * \return void
 *
 */
void printKvadratList(KvadratNode *list, MODES mode);

#endif // KVADRAT_H
