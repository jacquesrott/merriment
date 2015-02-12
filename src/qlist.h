#ifndef DW_QLIST_H
#define DW_QLIST_H

typedef struct {
    void* content;
    QListItem* previous;
    QListItem* next;
} QListItem;


typedef struct {
    unsigned int length;

    QListItem* head;
    QListItem* tail;
} QList;


QList* qlist_create();
void qlist_destroy(QList* qlist);

QListItem* qlist_push(QList* qlist, void* content);
QListItem* qlist_pop(QList* qlist);
QListItem* qlist_remove(QList* qlist, void* content);
void qlist_clear(QList* qlist);

QListItem* qlist_iter(QList* qlist);
QListItem* qlist_next(QListItem* item);

QListItem* qlistitem_create(void* content, QListItem* previous, QListItem* next);
void qlistitem_destroy(QListItem* item);

#endif