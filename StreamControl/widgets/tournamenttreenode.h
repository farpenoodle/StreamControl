#ifndef WIDGETS_TOURNAMENTTREENODE_H
#define WIDGETS_TOURNAMENTTREENODE_H

#include <QString>

// A class to help represent the structure of a tournament's matches
class TournamentTreeNode
{
public:
    TournamentTreeNode() {}

    TournamentTreeNode(QString child1Id, QString child2Id)
        : child1Id(child1Id), child2Id(child2Id) {}

    // The prerequisite matches
    QString child1Id, child2Id;
};

#endif //WIDGETS_TOURNAMENTTREENODE_H
