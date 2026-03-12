
const char* numberToCat(int number){
    static const char* cat_names[] = {
        "eeee", "eeem", "eeet", "eemm", "eemt", "eett",
                "emem", "emet", "emmm", "emmt", "emtt",
                        "etet", "etmm", "etmt", "ettt",
                                "mmmm", "mmmt", "mmtt",
                                        "mtmt", "mttt",
                                                "tttt",
          "eee", "eem", "eet",
          "eme", "emm", "emt",
          "ete", "etm", "ett",
          "mme", "mmm", "mmt",
          "mte", "mtm", "mtt",
          "tte", "ttm", "ttt",
          "ee","em","et","mm","mt","tt"};
 	// Check if the index is within the valid range
    if (number < 1 || number > sizeof(cat_names)) {
        return "Invalid";
    }
    // Return the corresponding cat name
    return cat_names[number - 1];
}

int catToNumber(std::string_view cat) {
    static constexpr std::string_view cat_names[] = {
        "eeee","eeem","eeet","eemm","eemt","eett",
        "emem","emet","emmm","emmt","emtt",
        "etet","etmm","etmt","ettt",
        "mmmm","mmmt","mmtt",
        "mtmt","mttt",
        "tttt",
        "eee","eem","eet",
        "eme","emm","emt",
        "ete","etm","ett",
        "mme","mmm","mmt",
        "mte","mtm","mtt",
        "tte","ttm","ttt",
        "ee","em","et","mm","mt","tt"
    };

    constexpr int size = sizeof(cat_names) / sizeof(cat_names[0]);
    for (int i = 0; i < size; ++i) {
        if (cat == cat_names[i]) return i + 1; // 1-indexed
    }
    return -1; // not found
}


int cat_lepCount(string cat, char lep1, char lep2){//usully I count only e and m. 
    int count = 0;
    for (int i = 0; i<cat.length(); i++){
        if (cat[i] == lep1 or cat[i] == lep2 )
            count++;
    }
    return count;
}
