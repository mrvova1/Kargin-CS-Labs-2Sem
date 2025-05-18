#pragma once
#include <string>

struct Tag {
    int           id;            // уникальный идентификатор
    std::string   name;          // текстовое имя
    double        globalWeight;  // вес в глобальном ранжировании
    double        eventWeight;   // дополнительный вес в ивентах

    Tag(int id_, const std::string& name_)
      : id(id_), name(name_), globalWeight(1.0), eventWeight(0.0) {}
};
