#pragma once

#include "core/Context.h"

namespace aria {
namespace tpcc {

enum class TPCCWorkloadType { NEW_ORDER_ONLY, PAYMENT_ONLY, MIXED };

class Context : public aria::Context {
public:
  TPCCWorkloadType workloadType = TPCCWorkloadType::NEW_ORDER_ONLY;

  Context get_single_partition_context() const {
    Context c = *this;
    c.newOrderCrossPartitionProbability = 0;
    c.paymentCrossPartitionProbability = 0;
    c.operation_replication = this->operation_replication;
    c.star_sync_in_single_master_phase = false;
    return c;
  }

  Context get_cross_partition_context() const {
    Context c = *this;
    c.newOrderCrossPartitionProbability = 100;
    c.paymentCrossPartitionProbability = 100;
    c.operation_replication = false;
    c.star_sync_in_single_master_phase = this->star_sync_in_single_master_phase;
    return c;
  }

  int n_district = 10;
  int newOrderCrossPartitionProbability = 10; // 表示新订单跨分区概率，默认为 10%
  int paymentCrossPartitionProbability = 15;  // 表示付款跨分区概率，默认为 15%
  bool write_to_w_ytd = true;
  bool payment_look_up = false;
};
} // namespace tpcc
} // namespace aria
