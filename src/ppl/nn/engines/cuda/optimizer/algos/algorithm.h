#ifndef _ST_HPC_PPL_NN_ENGINES_CUDA_OPTIMIZER_ALGOS_ALGORITHM_H_
#define _ST_HPC_PPL_NN_ENGINES_CUDA_OPTIMIZER_ALGOS_ALGORITHM_H_

#include <set>
#include <map>
#include <vector>
#include <string>

#include "ppl/common/types.h"
#include "ppl/nn/ir/graph.h"
#include "ppl/nn/engines/cuda/optimizer/opt_kernel.h"

#define ALGO_MAX_TIME (3.0e+10)
#define ALGO_INVALID_TIME (3.0e+11)

#define ALLOC_BUFFERF_FOR_ALGO_SELECT(buffer_name, size, callback)                           \
    BufferDesc buffer_name;                                                                  \
    status = options.device->ReallocWithRandomValue(size, &buffer_name);                     \
    if (status != RC_SUCCESS) {                                                              \
        LOG(DEBUG) << "alloc " #buffer_name " tensor failed";                                \
        return callback;                                                                     \
    }                                                                                        \
    BufferDescGuard __##buffer_name##_guard__(&buffer_name, [&options](BufferDesc* buffer) { \
        options.device->Free(buffer);                                                        \
    });

namespace ppl { namespace nn { namespace cuda {

class Algorithm {
public:
    virtual const bool IsRepeatable() {
        return true;
    }
    virtual const bool IsSupported() {
        return true;
    }
    virtual const bool CanSupportDynamic() {
        return true;
    }

    virtual const std::map<ppl::common::dataformat_t, std::set<ppl::common::dataformat_t>> Getformats(
        const std::string& type_name) = 0;
    virtual void GetAttrParam(void*& param) = 0;
    virtual void DeleteAttrParam(void*& param) = 0;

    virtual const double ExcuteTimer(ir::Node* node, OptKernelOptions& options) = 0;
    virtual ppl::common::RetCode ModifyParam(const ir::Node*, OptKernelOptions& options) = 0;
    virtual void ReshapeOnEdges(const ir::Node* node, std::map<edgeid_t, std::unique_ptr<TensorImpl>>* tensors,
                                ppl::common::dataformat_t input_format, ppl::common::dataformat_t output_format) = 0;
};

}}} // namespace ppl::nn::cuda

#endif