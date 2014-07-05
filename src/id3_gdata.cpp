#include <id3_gdata.h>

namespace id3 {

GlobalData* GlobalData::_instance = nullptr;

int GlobalData::init(const std::string& file) {
    int ret = 0;
    char line[MAX_CORPUS_LINE_LEN];
    int attr_index_array[MAX_ATTR_TYPE_COUNT];
    Sign sign;
    int line_index = 0;
    std::vector<std::map<uint64_t, int> > attr_value_index_maps;

    /// open corpus
    FILE* fp = fopen(file.c_str(), "r");
    if (nullptr == fp) {
        std::cerr << "open corpus file " << file.c_str() << " failed" << std::endl;
        clear();
        return -1;
    }

    /// read the first line
    /// the first line is the standard line
    int attr_cnt = 0;
    if (fgets(line, MAX_CORPUS_LINE_LEN, fp)) {
        attr_index_array[0] = 0;
        for (int i = 0; line[i] != '\0'; ++i) {
            char* pc = line + i;
            if (CORPUS_SPLIT_CHAR == *pc) {
                *pc = '\0';
                if (line[i + 1] != '\0') {
                    attr_index_array[++attr_cnt] = i + 1;
                }
            }
        }
    }
    if (attr_cnt < 1) {
        std::cerr << "corpus fields count is at least 2" << std::endl;
        ret = -1;
        clear();
        goto EXIT;
    }

    /// process first line and init attr value set
    attr_value_index_maps.resize((size_t)attr_cnt);
    for (int i = 0; i < attr_cnt; ++i) {
        const char* cur_attr = line + attr_index_array[i];
        if (0 != create_sign_64(cur_attr, strlen(cur_attr), sign)) {
            std::cerr << "create sign for " << cur_attr << " failed" << std::endl;
            continue;
        }
        attr_value_index_maps.at(i).insert(std::pair<uint64_t, int>(sign.s, 0));
        _globle_attr_set.insert(i);
        _globle_corpus_set.insert(line_index);
        _corpus_table[line_index][i] = 0;
    }
    if (0 == strncmp(POS_SAMPLE_SIGN, line + attr_index_array[attr_cnt], strlen(POS_SAMPLE_SIGN))) {
        _corpus_value[line_index++] = 1;
    } else {
        _corpus_value[line_index++] = 0;
    }

    /// read and set other lines
    while (fgets(line, MAX_CORPUS_LINE_LEN, fp)) {
        int cur_attr_cnt = 0;
        for (int i = 0; line[i] != '\0'; ++i) {
            char* pc = line + i;
            if (CORPUS_SPLIT_CHAR == *pc) {
                *pc = '\0';
                if (line[i + 1] != '\0') {
                    attr_index_array[++cur_attr_cnt] = i + 1;
                }
            }
        }
        if (cur_attr_cnt != attr_cnt) {
            std::cerr << "bad format in line " << line_index++ << std::endl;
            continue;
        }

        for (int i = 0; i < attr_cnt; ++i) {
            const char* cur_attr = line + attr_index_array[i];
            if (0 != create_sign_64(cur_attr, strlen(cur_attr), sign)) {
                std::cerr << "create sign for " << cur_attr << " failed" << std::endl;
                continue;
            }
            auto iter = attr_value_index_maps.at(i).find(sign.s);
            if (iter == attr_value_index_maps.at(i).end()) {
                int attr_value = attr_value_index_maps.at(i).size();
                _corpus_table[line_index][i] = attr_value;
                attr_value_index_maps.at(i).insert(std::pair<uint64_t, int>(sign.s, attr_value));
            } else {
                _corpus_table[line_index][i] = iter->second;
            }
            _globle_corpus_set.insert(line_index);
        }
        if (0 == strncmp(POS_SAMPLE_SIGN, line + attr_index_array[attr_cnt], strlen(POS_SAMPLE_SIGN))) {
            _corpus_value[line_index++] = 1;
        } else {
            _corpus_value[line_index++] = 0;
        }
    }

    /// set global data
    _attr_count = attr_cnt;
    _corpus_count = line_index;
    for (int i = 0; i < _attr_count; ++i) {
        _attr_value_count[i] = attr_value_index_maps.at(i).size();
    }

EXIT:
    fclose(fp);
    return ret;
}

void GlobalData::clear() {
    _corpus_count = 0;
    _attr_count = 0;
    _globle_corpus_set.clear();
    _globle_attr_set.clear();
}

double GlobalData::get_entropy(const std::set<int> &corpus) {
    auto flg2 = [](double d) {
        return log(d) / log(2);
    };
    int pos_cnt = 0, neg_cnt = 0, sum = corpus.size();
    double ans = 0.0;
    for(auto cp : corpus) {
        int is_pos = is_pos_corpus(cp);
        if (1 == is_pos) {
            ++pos_cnt;
        } else if (0 == is_pos) {
            ++neg_cnt;
        } else {
            --sum;
        }
    }  
    
    if (0 == pos_cnt || 0 == neg_cnt) {
        ans = 0.0;
    } else {
        ans = - (double)pos_cnt / sum * flg2((double)pos_cnt / sum)
            - (double)neg_cnt / sum * flg2((double)neg_cnt / sum);
    }
    return ans;  
}

}
