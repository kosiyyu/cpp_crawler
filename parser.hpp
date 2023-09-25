#include "cpp_crawler.h"
#include <string>
#include <iostream>

class Parser {
private:
    GumboOutput* output = nullptr;

public:
    Parser(const std::string& html_string) {
        output = gumbo_parse(html_string.c_str());
    }

    ~Parser() {
        if (output != nullptr) {
            gumbo_destroy_output(&kGumboDefaultOptions, output);
        }
    }

    bool isNode(GumboNode* node) {
        return node->type == GUMBO_NODE_ELEMENT;
    }

    bool isEmpty(GumboNode* node) {
        return node->v.element.children.length == 0;
    }

    void extract_data() {
        if (output == nullptr || !isNode(output->root)) {
            return;
        }
        GumboNode* root = output->root;
        find_by_partial_id(root, "post-title-t3_16");
    }

    void find_by_partial_id(GumboNode* node, std::string partialId) {
        if (isNode(node)) {
            GumboAttribute* attribute = gumbo_get_attribute(&node->v.element.attributes, "id");
            if (attribute != nullptr) {
                if (std::string(attribute->value).find(partialId) != std::string::npos) {
                    GumboVector* gumbo_node_vector = &node->v.element.children;
                    for (int i = 0; i < gumbo_node_vector->length; i++) {
                        GumboNode* local = static_cast<GumboNode*>(gumbo_node_vector->data[i]);
                        if (local->type == GUMBO_NODE_TEXT) {
                            std::cout << local->v.text.text;
                        }
                    }
                }
            }
            GumboVector* gumbo_node_vector = &node->v.element.children;
            for (int i = 0; i < gumbo_node_vector->length; i++) {
                GumboNode* local = static_cast<GumboNode*>(gumbo_node_vector->data[i]);
                find_by_partial_id(local, partialId);
            }
        }
    }
};
