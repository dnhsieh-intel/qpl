/*******************************************************************************
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 ******************************************************************************/

#include "compression_huffman_table.hpp"
#include "../../../sources/c_api/compression_operations/huffman_table.hpp"

namespace qpl::test {
void fill_compression_table(qpl_huffman_table_t table) {
    auto table_ptr = own_huffman_table_get_compression_table(table);

    uint32_t *literals_lengths_ptr = get_literals_lengths_table_ptr(table_ptr);
    uint32_t *offsets_ptr = get_offsets_table_ptr(table_ptr);

    for (uint32_t i = 0; i < 286; i++) {
        literals_lengths_ptr[i] = literals_match_table[i];
    }

    for (uint32_t i = 0; i < 30; i++) {
        offsets_ptr[i] = offsets_table[i];
    }

    for (uint32_t i = 0; i < 206; i++) {
        get_deflate_header_ptr(table_ptr)[i] = deflate_header[i];
    }

    set_deflate_header_bits_size(table_ptr, 1002u);

    ml::compression::qpl_compression_table_to_isal(reinterpret_cast<qplc_huffman_table_default_format *>
                                                            (get_sw_compression_huffman_table_ptr(table_ptr)),
                                                   reinterpret_cast<isal_hufftables *>
                                                            (get_isal_compression_huffman_table_ptr(table_ptr)));
}
}
