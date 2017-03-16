/*
 * Copyright (c) 2015 Cryptonomex, Inc., and contributors.
 *
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once

#include <graphene/chain/protocol/types.hpp>
#include <graphene/chain/protocol/base.hpp>

namespace graphene { namespace chain {


enum betting_market_type {
   moneyline,
   spread,
   over_under,
   BETTING_MARKET_TYPE_COUNT
};

struct moneyline_market_options {};

struct spread_market_options {
   int32_t margin;
};

struct over_under_market_options {
   uint32_t score;
};

typedef static_variant<moneyline_market_options, spread_market_options, over_under_market_options> betting_market_options_type;

struct betting_market_group_create_operation : public base_operation
{
   struct fee_parameters_type { uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION; };
   asset             fee;

   /**
    * This can be a event_id_type, or a
    * relative object id that resolves to a event_id_type
    */
   object_id_type event_id;

   betting_market_options_type options;

   extensions_type   extensions;

   account_id_type fee_payer()const { return GRAPHENE_WITNESS_ACCOUNT; }
   void            validate()const;
};

struct betting_market_create_operation : public base_operation
{
   struct fee_parameters_type { uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION; };
   asset             fee;

   /**
    * This can be a betting_market_group_id_type, or a
    * relative object id that resolves to a betting_market_group_id_type
    */
   object_id_type group_id;

   internationalized_string_type payout_condition;

   asset_id_type asset_id;

   extensions_type   extensions;

   account_id_type fee_payer()const { return GRAPHENE_WITNESS_ACCOUNT; }
   void            validate()const;
};

} }

FC_REFLECT_ENUM( graphene::chain::betting_market_type, (moneyline)(spread)(over_under)(BETTING_MARKET_TYPE_COUNT) )

FC_REFLECT( graphene::chain::moneyline_market_options, )
FC_REFLECT( graphene::chain::spread_market_options, (margin) )
FC_REFLECT( graphene::chain::over_under_market_options, (score) )
FC_REFLECT_TYPENAME( graphene::chain::betting_market_options_type )

FC_REFLECT( graphene::chain::betting_market_group_create_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::betting_market_group_create_operation, 
            (fee)(event_id)(options)(extensions) )

FC_REFLECT( graphene::chain::betting_market_create_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::betting_market_create_operation, 
            (fee)(group_id)(payout_condition)(asset_id)(extensions) )