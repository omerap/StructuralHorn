#pragma once

#include <iostream>
#include <set>
#include <unordered_map>
#include <exception>

#include "Global.h"

namespace structuralHorn {
	
	typedef std::set<int> node_set;
	typedef std::multiset<int> node_multiset;
	typedef std::set<int> hyperarc_set;
	typedef std::unordered_map<int, hyperarc_set> out_hyperarcs_map;
	typedef std::unordered_map<int, node_multiset> source_nodes_map;
	typedef std::unordered_map<int, int> target_node_map;
	typedef std::unordered_map<int, bool> reachable_map;
	typedef std::unordered_map<int, size_t> weights_map;

	struct invalidNodeId : public std::exception {
	public:
		const char* what() const throw () {
			return "Invalid node id. The id should be between 0 and number of predicates + 1";
		}
	};

	struct invalidHyperarcId : public std::exception {
	public:
		const char* what() const throw () {
			return "Invalid hyperarc id. The id should be between 1 and number of clauses";
		}
	};

	class hypergraph {
	private:
		int init_node;
		int err_node;
		node_set reachable;

		node_set nodes;
		out_hyperarcs_map out_hyperarcs; // node -> outgoing hyperarcs
		source_nodes_map source_nodes; // hyperarc -> source nodes
		target_node_map target_node; // hyperarc -> target node
		weights_map weight; // hyperarc -> weight
			
	public:
		hypergraph (int init_node, int err_node) : init_node(init_node), err_node(err_node) {}

		// TODO: insert all hyperarcs in the constructor and delete this function
		void insert_hyperarc (int hyperarc, node_multiset source_nodes, int target_node) {
			for (int source_node : source_nodes) {
				this->out_hyperarcs[source_node].insert(hyperarc);
				this->nodes.insert(source_node);
			}
			this->nodes.insert(target_node);
			this->source_nodes[hyperarc] = source_nodes;
			this->target_node[hyperarc] = target_node;
			if (gParams.hyperarc_weight_distance_measure == 0) {
				this->weight[hyperarc] = source_nodes.size();
			}
			else {
				this->weight[hyperarc] = 1;
			}
		}

		hyperarc_set shortest_nontrivial_hyperpath_gt0 () {
			hyperarc_set optimal_hyperpath;
			
			node_set nodes_to_scan(this->nodes);
			std::unordered_map<int, size_t> hyperarc_unscanned_sources;
			std::unordered_map<int, size_t> node_dist;
			std::unordered_map<int, size_t> hyperarc_dist;
			std::unordered_map<int, int> last_hyperarc;

			// initialize data structures
			for (int node : this->nodes) {
				node_dist[node] = SIZE_MAX;
				last_hyperarc[node] = INT_MAX;
			}

			for (const auto& [hyperarc, source_nodes] : this->source_nodes) {
				node_set unique_source_nodes(source_nodes.cbegin(), source_nodes.cend());
				hyperarc_unscanned_sources[hyperarc] = unique_source_nodes.size();
				hyperarc_dist[hyperarc] = SIZE_MAX;
			}

			// scan init_node and reachable nodes
			node_set sources_to_scan(reachable);
			sources_to_scan.insert(init_node);
			for (int node : sources_to_scan) {
				for (int hyperarc : out_hyperarcs[node]) {
					if (weight[hyperarc] == 0) {
						continue;
					}
					hyperarc_unscanned_sources[hyperarc]--;
					if (hyperarc_unscanned_sources[hyperarc] == 0) {
						hyperarc_dist[hyperarc] = 0;
						int target = target_node[hyperarc];
						if (node_dist[target] > weight[hyperarc]) {
							node_dist[target] = weight[hyperarc];
							last_hyperarc[target] = hyperarc;
						}
					}
					nodes_to_scan.erase(node);
				}
			}
			
			// scan the rest of the nodes.
			while (!nodes_to_scan.empty()) {
				
				// find unscanned node with minimal distance
				auto it = nodes_to_scan.cbegin();
				size_t min_dist = node_dist[*it];
				int min_node = *it;
				it++;
				while (it != nodes_to_scan.cend()) {
					if (min_dist > node_dist[*it]) {
						min_dist = node_dist[*it];
						min_node = *it;
					}
					it++;
				}

				// scan the minimal node
				for (int hyperarc : out_hyperarcs[min_node]) {
					if (weight[hyperarc] == 0) {
						continue;
					}
					hyperarc_unscanned_sources[hyperarc]--;
					if (hyperarc_unscanned_sources[hyperarc] == 0) {
						
						// compute hyperarc distance
						hyperarc_dist[hyperarc] = 0;
						if (gParams.hyperarc_sources_distance_measure == 0) {
							node_set unique_source_nodes(source_nodes[hyperarc].cbegin(), source_nodes[hyperarc].cend());
							for (int hyperarc_source : unique_source_nodes) {
								if ((hyperarc_source != init_node) && (reachable.count(hyperarc_source) == 0)) {
									hyperarc_dist[hyperarc] += node_dist[hyperarc_source];
								}
							}
						}
						else {
							for (int hyperarc_source : source_nodes[hyperarc]) {
								if ((hyperarc_source != init_node) && (reachable.count(hyperarc_source) == 0)) {
									hyperarc_dist[hyperarc] += node_dist[hyperarc_source];
								}
							}
						}
						
						// visit the target of the hyperarc
						int target = target_node[hyperarc];
						if (node_dist[target] > hyperarc_dist[hyperarc] + weight[hyperarc]) {
							node_dist[target] = hyperarc_dist[hyperarc] + weight[hyperarc];
							last_hyperarc[target] = hyperarc;
						}
					}
				}

				nodes_to_scan.erase(min_node);
			}

			// find last node in an optimal hyperpath
			node_set targets_to_check(reachable);
			targets_to_check.insert(err_node);
			auto it = targets_to_check.cbegin();
			size_t min_dist = node_dist[*it];
			int min_node = *it;
			it++;
			while (it != targets_to_check.cend()) {
				if (min_dist > node_dist[*it]) {
					min_dist = node_dist[*it];
					min_node = *it;
				}
				it++;
			}

			// std::cout << "\nOptimal hyperpath weight: " << min_dist;

			// construct the optimal hyperpath
			if (last_hyperarc[min_node] != INT_MAX) {
				int curr_hyperarc = last_hyperarc[min_node];
				optimal_hyperpath.insert(curr_hyperarc);
				node_set optimal_hyperpath_nodes_to_check;
				for (int hyperarc_source : source_nodes[curr_hyperarc]) {
					if ((hyperarc_source != init_node) && (reachable.count(hyperarc_source) == 0)) {
						optimal_hyperpath_nodes_to_check.insert(hyperarc_source);
					}
				}

				while (!optimal_hyperpath_nodes_to_check.empty()) {
					int curr_node = *(optimal_hyperpath_nodes_to_check.cbegin());
					optimal_hyperpath_nodes_to_check.erase(curr_node);
					int curr_hyperarc = last_hyperarc[curr_node];
					optimal_hyperpath.insert(curr_hyperarc);
					for (int hyperarc_source : source_nodes[curr_hyperarc]) {
						if ((hyperarc_source != init_node) && (reachable.count(hyperarc_source) == 0)) {
							optimal_hyperpath_nodes_to_check.insert(hyperarc_source);
						}
					}
				}
			}

			// zero the weights of the optimal hyperpath hyperarcs and mark their target nodes as reachable
			for (int hyperarc : optimal_hyperpath) {
				weight[hyperarc] = 0;
				if (this->target_node[hyperarc] != err_node) {
					reachable.insert(target_node[hyperarc]);
				}
			}

			return optimal_hyperpath;
		}

		hyperarc_set get_out_hyperarcs(int node) {
			// assert(0 <= init_node && node <= this->err_node);
			if (node < this->init_node || node > this->err_node) {
				throw invalidNodeId();
			}
			return this->out_hyperarcs[node];
		}

		int get_target_node(int hyperarc) {
			if (this->target_node.count(hyperarc) == 0) {
				throw invalidHyperarcId();
			}
			return this->target_node[hyperarc];
		}

		friend std::ostream& operator<<(std::ostream& out, hypergraph& g);
	};

	inline std::ostream& operator<<(std::ostream& out, hypergraph& g) {
		out << "=================================================================\n";
		out << "my hypergraph has " << g.out_hyperarcs.size() << " nodes and " << g.source_nodes.size() << " hyperarcs.\n\n";
		out << "the outgoing hyperarcs of each node: \n";
		for (int node : g.nodes) {
			out << "- node " << node << ":";
			if (node == g.init_node) {
				out << " init node";
			}
			else if (node == g.err_node) {
				out << " error node";
			}
			else {
				if (g.reachable.count(node)) {
					out << "reachable";
				}
				else {
					out << "not reachable";
				}
			}
			out << "\n";
			for (int hyperarc : g.out_hyperarcs[node]) {
				out << "\t--[" << hyperarc << "]--> " << g.target_node[hyperarc] << "\n";
			}
		}

		out << "\nthe set of hyperarcs:\n";
		for (const auto& [hyperarc, source_nodes] : g.source_nodes) {
			out << "\t{";
			bool first_node = true;
			for (int source_node : source_nodes) {
				if (first_node) {
					first_node = false;
					out << source_node;
				}
				else {
					out << ", " << source_node;
				}
			}
			out << "}     \t--[" << hyperarc << "]--> " << g.target_node[hyperarc] 
				<< "\tweight = " << g.weight[hyperarc] << "\n";
		}
		out << "=================================================================\n";
		return out;
	}

}