/**
 *  @dev minakokojima, yukiexe
 *  @copyright Andoromeda
 */
#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/transaction.hpp>
 
#define TOKEN_CONTRACT N(dacincubator)
#define TOKEN_SYMBOL S(4, PLT)

typedef double real_type;
typedef uint8_t card ;

using std::string;
using eosio::symbol_name;
using eosio::asset;
using eosio::symbol_type;
using eosio::permission_level;
using eosio::action;

class council : public eosio::contract {
    public: council(account_name self) :
        contract(self),
        _voters(_self, _self),
        _proxies(_self, _self),
        _council(_self, _self){}
    
    void stake(account_name from, uint64_t delta) {
        auto itr = _voters.find(from);
        if (itr == _voters.end()) {    
            _voters.emplace(_self, [&](auto &v) {
                v.owner = from;
                v.staked += delta;
                v.last_vote_time = now();
            });
        } else {  
            _voters.modify(itr, 0, [&](auto &v) {
                v.staked += delta;
                v.last_vote_time = now();
            });
        }
    }

    void unstake(account_name from) {
        
    }    

    void vote(account_name from) {

    }

    void runproxy(account_name from) {

    }    

    void runcouncil(account_name from) {

    }        

    // @abi table voter_table
    struct voter_info {
        account_name owner = 0; /// the voter
        account_name proxy = 0; /// the proxy set by the voter, if any
        account_name council;   /// the producers approved by this voter if no proxy set
        uint64_t     staked = 0;
        time         last_vote_time = 0; 

        uint64_t primary_key()const { return owner; }
    };       

    // @abi table proxy_table
    struct proxy_info {
        account_name owner = 0; /// the voter
        account_name council; /// the producers approved by this voter if no proxy set
        uint64_t     staked = 0;
        uint64_t     delegated_staked = 0;
        time         last_vote_time = 0; 

        uint64_t primary_key()const { return owner; }
    };

    // @abi table council_table
    struct council_info {
        account_name owner = 0; /// the voter
        account_name council; /// the producers approved by this voter if no proxy set
        uint64_t     total_votes = 0;
        uint64_t     unpaid = 0;

        uint64_t primary_key()const { return owner; }
    };          

    typedef eosio::multi_index<N(voters),  voter_info>  voters_table;
    typedef eosio::multi_index<N(proxies), voter_info>  proxies_table;
    typedef eosio::multi_index<N(council), voter_info>  council_table;    
    voters_table _voters;
    proxies_table _proxies;
    council_table _council;
};