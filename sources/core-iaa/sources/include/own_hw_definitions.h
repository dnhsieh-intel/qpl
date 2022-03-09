/*******************************************************************************
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 ******************************************************************************/

#ifndef HW_PATH_OWN_HW_DEFINITIONS_H_
#define HW_PATH_OWN_HW_DEFINITIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define IMMEDIATELY_COMPLETE     0xFFFFu                      /**< @todo */
#define MAX_BUF_SIZE             (1024u * 1024 * 1024u)       /**< @todo */

/* ------ Operations ------ */
/**
 * @name Operation code flags
 * @anchor HW_OPERATION_FLAGS
 * @todo Opcode values
 * @{
 */

// the following aids opcode parsing
#define QPL_OPCODE_Z_MASK       0xF8u    /**< @todo  either DECOMP or COMP */
#define QPL_OPCODE_Z            0x48u    /**< @todo */
#define QPL_OPCODE_Z_MASK2      0xFCu    /**< @todo One or the other */
#define QPL_OPCODE_Z_DECOMP     0x48u    /**< @todo */
#define QPL_OPCODE_Z_COMP       0x4Cu    /**< @todo */

// Read Src2 values
#define AD_RDSRC2_UNUSED        0u  /**< @todo */
#define AD_RDSRC2_AECS          1u  /**< @todo */
#define AD_RDSRC2_FF_INPUT      2u  /**< @todo */

// Write Src2 values
#define AD_WRSRC2_NEVER         0u  /**< @todo */
#define AD_WRSRC2_ALWAYS        1u  /**< @todo */
#define AD_WRSRC2_MAYBE         2u  /**< @todo */

// End Process values
#define AD_APPEND_NOTHING       0u  /**< @todo */
#define AD_APPEND_EOB           1u  /**< @todo */
#define AD_APPEND_EOB_SB        2u  /**< Append EOB and non-b_final Store Block */
#define AD_APPEND_EOB_FINAL_SB  3u  /**< Append EOB and b_final Store Block */
/** @} */

/* ------ Setters ------ */
/**
 * @name Operations codes and operation flags setters
 * @anchor HW_OPERATIONS_AND_FLAGS_SETTERS
 * @todo
 * @{
 */
// opcode_opflags fields
#define ADOF_READ_SRC2(x)       (((x) & 3u) << 16u)     /**< @todo */
#define ADOF_WRITE_SRC2(x)      (((x) & 3u) << 18u)     /**< @todo */
#define ADOF_CRC32C             (1u << 21u)             /**< @todo */
#define ADOF_AECS_SEL           (1u << 22u)             /**< @todo */
#define ADOF_OPCODE(x)          (((x) & 0xFFu) << 24u)  /**< @todo */
#define ADOF_GET_OPCODE(x)      (((x) >> 24u) & 0xFFu)  /**< @todo */

// decompression flags
#define ADDF_ENABLE_DECOMP      (1u << 0u)              /**< @todo */
#define ADDF_FLUSH_OUTPUT       (1u << 1u)              /**< @todo */
#define ADDF_STOP_ON_EOB        (1u << 2u)              /**< @todo */
#define ADDF_CHECK_FOR_EOB      (1u << 3u)              /**< @todo */
#define ADDF_SEL_BFINAL_EOB     (1u << 4u)              /**< @todo */
#define ADDF_DECOMP_BE          (1u << 5u)              /**< @todo */
#define ADDF_IGNORE_END_BITS(x) (((x) & 7u) << 6u)      /**< @todo */
#define ADDF_SUPPRESS_OUTPUT    (1u << 9u)              /**< @todo */
#define ADDF_ENABLE_IDXING(x)   (((x) & 7u) << 10u)     /**< @todo */

// compression flags
#define ADCF_STATS_MODE         (1u << 0u)              /**< @todo */
#define ADCF_FLUSH_OUTPUT       (1u << 1u)              /**< @todo */
#define ADCF_END_PROC(x)        (((x) & 3u) << 2u)      /**< @todo */
#define ADCF_GEN_LITS           (1u << 4u)              /**< @todo */
#define ADCF_COMP_BE            (1u << 5u)              /**< @todo */
#define ADCF_ENABLE_IDXING(x)   (((uint32_t)(x) & 7u) << 6u)      /**< @todo */

// crc64 flags
#define ADC64F_INVCRC           (1u << 14u)             /**< @todo */
#define ADC64F_BE               (1u << 15u)             /**< @todo */

// filter flags
#define ADFF_OUT_BE             (1u << 15u)             /**< @todo */
#define ADFF_INV_OUTPUT         (1u << 16u)             /**< @todo */
/** @} */


/* ====== Macros ====== */

/**
 * @todo
 */
#define QPL_FILTER_OP (\
    (QPL_ONE_64U << qpl_op_set_membership) |\
    (QPL_ONE_64U << qpl_op_extract       ) |\
    (QPL_ONE_64U << qpl_op_select        ) |\
    (QPL_ONE_64U << qpl_op_rle_burst     ) |\
    (QPL_ONE_64U << qpl_op_find_unique   ) |\
    (QPL_ONE_64U << qpl_op_expand        ) |\
    (QPL_ONE_64U << qpl_op_scan_eq       ) |\
    (QPL_ONE_64U << qpl_op_scan_ne       ) |\
    (QPL_ONE_64U << qpl_op_scan_lt       ) |\
    (QPL_ONE_64U << qpl_op_scan_le       ) |\
    (QPL_ONE_64U << qpl_op_scan_gt       ) |\
    (QPL_ONE_64U << qpl_op_scan_ge       ) |\
    (QPL_ONE_64U << qpl_op_scan_range    ) |\
    (QPL_ONE_64U << qpl_op_scan_not_range))

/**
 * @todo
 */
#define QPL_SRC2_OP (\
    (QPL_ONE_64U << qpl_op_set_membership) |\
    (QPL_ONE_64U << qpl_op_select        ) |\
    (QPL_ONE_64U << qpl_op_rle_burst     ) |\
    (QPL_ONE_64U << qpl_op_expand        ))

#define QPL_OP_SCAN_FIRST qpl_op_scan_eq  /**< @todo */

/**
 * @todo Random Access Body is FLAG_RND_ACCESS and not FLAG_FIRST
 */
#define IS_RND_ACCESS_BODY(flag) \
    (((flag) & (QPL_FLAG_RND_ACCESS | QPL_FLAG_FIRST)) == QPL_FLAG_RND_ACCESS)

/**
 * @todo
 */
#define QPL_IS_FILTER_OP(op) (((uint64_t)QPL_FILTER_OP >> op) & 1u)

/**
 * @todo
 */
#define QPL_IS_SRC2_OP(op) (((uint64_t)QPL_SRC2_OP >> op) & 1u)

#define OWN_UNREFERENCED_PARAMETER(p) ((p)= 0) /**< Unreferenced parameter - warning removal */

/**
 * @todo
 */
#define GET_DCFG(p) ((hw_iaa_aecs_analytic *)(((uint8_t *)((p)->dcfg)) + ((p)->aecs_hw_read_offset)))

#ifdef __cplusplus
}
#endif

#endif //HW_PATH_OWN_HW_DEFINITIONS_H_