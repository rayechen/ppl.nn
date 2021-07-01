#ifndef _ST_HPC_PPL_NN_ENGINES_X86_OPTIMIZER_OPS_PPL_CHANNEL_SHUFFLE_OP_H_
#define _ST_HPC_PPL_NN_ENGINES_X86_OPTIMIZER_OPS_PPL_CHANNEL_SHUFFLE_OP_H_

#include "ppl/nn/params/ppl/channel_shuffle_param.h"
#include "ppl/nn/engines/x86/optimizer/opt_kernel.h"

namespace ppl { namespace nn { namespace x86 {

class ChannelShuffleOp final : public X86OptKernel {
public:
    ChannelShuffleOp(const ir::Node* node) : X86OptKernel(node) {}
    ppl::common::RetCode Init(const OptKernelOptions& options) override;
    KernelImpl* CreateKernelImpl() const override;
    ppl::common::RetCode SelectFormat(const InputOutputInfo& info,
                                      std::vector<ppl::common::dataformat_t>* selected_input_formats,
                                      std::vector<ppl::common::dataformat_t>* selected_output_formats) override;
    void SetGroup(int group);

private:
    std::shared_ptr<ppl::nn::common::ChannelShuffleParam> param_;
};

}}} // namespace ppl::nn::x86

#endif